/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/31 12:02:24y jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks a.out");
}
int	origin_in;
int	origin_out;

extern char **environ;

int main(int ac, char **av, char ** envp)
{
	readlilne_tester();
}

void	readlilne_tester(void)
{
	char	*temp;
	char	**token;
	char	**to_cmmand;
	int		i;
	t_mini	*node;

	while (1)
	{
		temp = readline("minishell : ");
		if (temp)
		{
			token = ft_split(temp, '|');
			int	i = 0;
			int	size = 0;
			while (token[i])
				i++;
			size = i;
			node = (t_mini *)malloc(sizeof(t_mini) * i);
			i = -1;
			while (token[++i])
			{
				to_cmmand = ft_split(token[i], ' ');
				node[i].command = to_cmmand;
				node[i].cnt = size;
				node[i].input_fd = 0;
				node[i].output_fd = 0;
				int	j = 0;
				while (to_cmmand[j])
					j++;
				node[i].cmd_size = j;
			}
			int	k = -1;
			while (++k < node->cnt)
			{
				for (int i = 0 ; i < node[k].cmd_size ; i++)
				{
					printf("%s\n", node[k].command[i]);
				}
				printf("------------------\n");
			}
			exec_cmd(node);
		}
	}
}

void	process_start2(t_mini *data)
{
	int		i;
	int		prev_pipe;
	int		cur_pipe[2];
	pid_t	pid;

	i = -1;
	prev_pipe = 0;

	while (++i < data->cnt)
	{
		pipe(cur_pipe);
		pid = fork();
		if (pid == 0)
		{	
			if (data->input_fd == - 1 || data->output_fd == -1)
				exit(128);
			if (is_argument(data[i].command, &data[i]))
			{
				if (data[i].input_fd)
					close(data[i].input_fd);
				data[i].input_fd = 0;
			}
			else if (data[i].input_fd != 0)
			{
				if (dup2(data[i].input_fd, 0) == -1)
					write(2, "in", 2);
				close(data[i].input_fd);
			}
			if (prev_pipe)
			{
				dup2(prev_pipe, 0);
				close(prev_pipe);
			}
			if (data[i].cnt > 1 && data[i].cnt - 1 != i)
			{
				close(cur_pipe[0]);
				dup2(cur_pipe[1], 1);
				close(cur_pipe[1]);
			}
			if (data[i].output_fd != 0)
			{
				dup2(data[i].output_fd, 1);
				close(data[i].output_fd);
			}
			cmd_find(&data[i]);
		}
		else if (pid > 0)
		{
			close(cur_pipe[1]);
			if (prev_pipe)
			{
				close(prev_pipe);
			}
			if (data[i].cnt > 1)
			{
				prev_pipe = cur_pipe[0];
			}
			else
			{
				close(cur_pipe[0]);
			}
		}
		else
			error_fork();
	}
	while (i)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
}

int	is_argument(char **command, t_mini *data)
{
	int	i;
	int	is_argument;

	i = -1;
	is_argument = 0;
	while (++i < data->cmd_size)
	{
		if (data->command[i] == NULL)
			continue;
		else if (ft_strncmp("-", data->command[i], 1) != 0)
			is_argument++;
	}
	if (is_argument > 1)
		return (1);
	return (0);
}

void	cmd_find(t_mini *data)
{
	char	*temp;
	char	**split_path;
	
	temp = getenv("PATH");
	split_path = ft_split(temp, ':');
	cmd_start(data, split_path);
}

void	cmd_start(t_mini *data, char **split_path)
{
	char	*slash_join;
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	while (split_path[++i])
	{
		slash_join = ft_strjoin(split_path[i], "/");
		j = -1;
		while (++j < data->cmd_size)
		{
			if (data->command[j] != NULL)
			{
				cmd = ft_strjoin(slash_join, data->command[j]);
				if (access(cmd, X_OK) == 0)
				{
					// for(int i = 0 ; i < data->cmd_size ; i++)
					// {
					// 	write(2, data->command[i], ft_strlen(data->command[i]));
					// }
					command_realloc(data);
					if (execve(cmd, data->command, NULL) == -1)
					{
						error_execve();
					}
				}
				free(cmd);
			}
		}
		free(slash_join);
	}
	error_cmdnotfound(data->command[0], data);
}

void	command_realloc(t_mini *data)
{
	int		i;
	int		j;
	int		token_cnt;
	char	**new_token;

	i = -1;
	token_cnt = 0;
	if (data)
	{
		if (data->command)
		{
			while (++i < data->cmd_size)
			{
				if (data->command[i])
					token_cnt++;
			}
		}
	}
	else if (!data || !data->command) 
		return ;
	new_token = (char **)malloc(sizeof(char *) * (token_cnt + 1));
	if (new_token)
		error_malloc();
	new_token[token_cnt] = NULL;
	i = -1;
	j = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i])
			new_token[++j] = ft_strdup(data->command[i]);
	}
	command_free(data->command);
	data->command = new_token;
}

void	command_free(char **command)
{
	int	i;

	i = -1;
	if (command)
	{
		while (command[++i])
			free(command[i]);
		free(command);
	}
}

void	exec_cmd(t_mini *data)
{
	int	i;

	i = -1;
	while (++i < data[0].cnt)
	{
		redirection_ready(&data[i]);
	}
	process_start2(data);
}

int	redirection_ready(t_mini *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i] && is_redirection(data->command[i]))
		{
			set_redirection(data, i);
		}
	}
	return (0);
}

void    set_redirection(t_mini *data, int i)
{
	if (!data->command[i])
		return ;
	if (is_redirection(data->command[i]) == 1)
		file_open(data, i);
	else if (is_redirection(data->command[i]) == 2)
		file_create(data, i, 0);
	else if (is_redirection(data->command[i]) == 3)
		file_create(data, i, 1);
}

void    file_create(t_mini *data, int i, int flag)
{
	int fd;

	if (i + 1 > data->cmd_size) // this condition need to be handle in parsing part
		exit(258);
	if (data->output_fd != 0)
		close(data->output_fd);
	if (flag)
	{    
		fd = open(data->command[i + 1],  O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			error_file();
	}
	else 
	{
		fd = open(data->command[i + 1],  O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			error_file();
	}
	data->output_fd = fd;
	set_cmd_null(data, i, i + 1);
}

void    file_open(t_mini *data, int i)
{
	char    *file_name;
	int     fd;

	if (i + 1 > data->cmd_size)
		exit(258);
	if (data->input_fd != 0)
	{
		close(data->input_fd);
	}
	file_name = data->command[i + 1];
	fd = open (file_name, O_RDONLY);
	if (fd == -1)
		error_file();
	data->input_fd = fd;
	set_cmd_null(data, i, i + 1);
}

void	set_cmd_null(t_mini *data, int start, int end)
{
	char	*temp;

	while (start <= end)
	{
		temp = data->command[start];
		data->command[start] = NULL;
		free(temp);
		start++;
	}
}

void	error_cmdnotfound(char *cmd, t_mini *data)
{
	char	*str;

	str = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
}

void	error_execve(void)
{
	perror("execve");
	exit(1);
}

void    error_file(void)
{
	perror("file");
}

void	error_fork(void)
{
	perror("fork");
	exit(1);
}

void	error_pipe(void)
{
	perror("pipe");
	exit(1);
}

void	error_malloc(void)
{
	perror("malloc");
	exit(1);
}

int is_redirection(char *str)
{
	// < > >> <>(?)
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (2);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (3);
	return (0);
}