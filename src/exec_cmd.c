/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/31 21:29:23 by jinhyeok         ###   ########.fr       */
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

	node = NULL;
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
			free(temp);
			exec_cmd(node);
			node_free(node);
			command_free(token);
		}
	}
}

void	node_free(t_mini *node)
{
	int	i;

	i = -1;
	if (node)
	{
		while (++i < node->cnt)
		{
			if (&node[i])
			{
				command_free(node[i].command);
			}
		}
		free(node);
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

	while ((++i < data->cnt))
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
			if (data->builtin_cnt == 1)
			{
				do_builtin(data);
				break;
			}
			close(cur_pipe[1]);
			if (prev_pipe)
				close(prev_pipe);
			if (data[i].cnt > 1)
				prev_pipe = cur_pipe[0];
			else
				close(cur_pipe[0]);
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

void	builtin_counter(t_mini *data)
{
	int	i;
	int	builtin_cnt;

	i = -1;
	builtin_cnt = 0;
	while (++i < data->cnt)
	{
		if (builtin_check(&data[i]))
			builtin_cnt++;
	}
	data->builtin_cnt = builtin_cnt;
}

int	builtin_check(t_mini *data)
{
	int		i;
	char	*temp;

	i = -1;
	while (++i < data->cmd_size)
	{
		temp = data->command[i];
		if (ft_strncmp(temp, "cd", ft_strlen(temp)) == 0)
			return (1);
		else if (ft_strncmp(temp, "echo", ft_strlen(temp)) == 0)
			return (2);
		else if (ft_strncmp(temp, "pwd", ft_strlen(temp)) == 0)
			return (3);
		else if (ft_strncmp(temp, "export", ft_strlen(temp)) == 0)
			return (4);
		else if (ft_strncmp(temp, "unset", ft_strlen(temp)) == 0)
			return (5);
		else if (ft_strncmp(temp, "env", ft_strlen(temp)) == 0)
			return (6);
		else if (ft_strncmp(temp, "exit", ft_strlen(temp)) == 0)
			return (7);
	}
	return (0);
}

void	do_builtin(t_mini *data)// seperate input &data[i];
{
	if (builtin_check(data) == 1)
		do_cd(data);
	else if (builtin_check(data) == 2)
	{

	}
		//do_echo(data);
}

void	do_echo(data)
{

}

void	do_cd(t_mini *data)
{
	char	*to_directory;
	
	to_directory = NULL;
	if (data->cmd_size > 1)
		to_directory = data->command[1];
	if (to_home_directory(to_directory))
	{
		ft_putstr_fd("to home directory", 2);
		return ;
		//get envp value set it// if the home value is nothing set => not set home error
	}
	if (to_back_directory(to_directory))
		return ;
	else if(chdir(to_directory) == -1)
	{
		perror(data->command[1]);
	}
}
int	to_back_directory(char *to_directory)
{
	if (ft_strncmp(to_directory, "-", ft_strlen(to_directory)) == 0)
	{
		//set_oldpwd;
		//get envp and go back 
		ft_putstr_fd("to back directory", 2);
		return (1);
	}
	else
		return (0);
}

int	to_home_directory(char *to_directory)
{
	if (!to_directory)
		return (1);
	if (is_redirection(to_directory)\
	|| !ft_strncmp(to_directory, ".", ft_strlen(to_directory)) \
	|| !ft_strncmp(to_directory, "~", ft_strlen(to_directory)))
		return (1);
	return (0);
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
	if (!new_token)
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
	builtin_counter(data);
	if (data->builtin_cnt == 1)
	{
		do_builtin(data);
		return ;
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

// file open and redirection fd set; 
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

//error msg

void	error_cmdnotfound(char *cmd, t_mini *data)
{
	char	*str;

	str = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	exit(128);
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
