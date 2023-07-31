/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/29 14:12:19by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	leaks(void)
{
	system("leaks a.out");
}
extern char **environ;

int main(int ac, char **av, char ** envp)
{
	t_mini	*data;
	
	char	*str;
	char	*str1;
	char	*str2;
	// char	*str3;
	// char	*str4;
	// char	*str5;

	str = ft_strdup("cat");
	str1 = ft_strdup("cat");
	str2 = ft_strdup("ls");
	// str3 = ft_strdup("cat");
	// str4 = ft_strdup(">");
	// str5 = ft_strdup("test2");

	// data = (t_mini *)malloc(sizeof(t_mini) * 2);
	// data[0].command = (char **)malloc(sizeof(char *) * 4);
	// data[1].command = (char **)malloc(sizeof(char *) * 4);
	// data[0].command[0] = str;
	// data[0].command[1] = str1;
	// data[0].command[2] = str2;
	// data[0].command[3] = NULL;

	// data[1].command[0] = str3;
	// data[1].command[1] = str4;
	// data[1].command[2] = str5;
	// data[1].command[3] = NULL;

	// data[0].cmd_size = 3;
	// data[0].node_id = 0;
	// data[1].cmd_size = 3;
	// data[1].node_id = 1;
	// data[0].cnt = 2;
	// data[1].cnt = 2;
	//atexit(leaks);
	
	data = (t_mini *)malloc(sizeof(t_mini) * 3);
	data[0].command = (char **)malloc(sizeof(char *) * 1);
	data[1].command = (char **)malloc(sizeof(char *) * 1);
	data[2].command = (char **)malloc(sizeof(char *) * 1);
	data[0].cnt = 3;
	data[1].cnt = 3;
	data[2].cnt = 3;
	data[0].cmd_size = 1;
	data[1].cmd_size = 1;
	data[2].cmd_size = 1;
	data[0].command[0] = str;
	data[1].command[0] = str1;
	data[2].command[0] = str2;
	// int	origin_in = dup(0);
	// int	origin_out = dup(1);
	// data[0].origin_in = origin_in;
	// data[0].origin_out = origin_out;
	exec_cmd(data); 
	//cmd_find_start(data);

	free(data[0].command);
	free(data);
}

void	cmd_find(t_mini *data)
{
	int	i;

	i = -1;
	char	*joined;
	char	*cmd;
	char *temp = getenv("PATH");
	char	**split;
	split = ft_split(temp, ':');

	while (split[++i])
	{
		joined = ft_strjoin(split[i], "/");
		for (int i = 0 ; i < data->cmd_size ; i++)
		{
			if (data->command[i] != NULL)
			{
				cmd = ft_strjoin(joined, data->command[i]);
				//printf("in");
			}
		}

		if (access(cmd, X_OK) == 0)
		{
			// 				ft_putstr_fd(data[0].command[0], 2);
			// for(int i = 0 ; i < data[0].cmd_size ; i++)
			// {
			// 	printf("%s", data[0].command[i]);
			// }
				//ft_putstr_fd("hihi\n", 2);
			if (execve(cmd, data[0].command, NULL) == -1)
			{
				printf("error");
			}
		}
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

// void	exec_ready(t_mini *data)
// {
// 	int	fd[2];

// 	if (pipe(fd) == -1);
// 		error_pipe();
// 	data->parent_pipe[0] = fd[0];
// 	data->parent_pipe[1] = fd[1];
// 	process_start(data);
// }

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
		if (pipe(cur_pipe) == -1)
			error_file();
		pid = fork();
		if (pid == - 1)
			error_fork();
		if (pid == 0)
		{	
			if (data[i].input_fd != 0)
			{
				dup2(data[i].input_fd, 0);
				close(data[i].input_fd);
			}
			if (prev_pipe)
			{
				dup2(prev_pipe, 0);
				close(prev_pipe);
			}
			if (data[i].cnt > 1)
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
			cmd_find(data);
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
				close(cur_pipe[1]);
			}
		}
		else
			error_fork();
	}
	while (i--)
	{
		waitpid(-1, NULL, 0);
	}
}

// void	process_start(t_mini *data)
// {
// 	int		i;
// 	int		cur_pipe[2];
// 	pid_t	id;

// 	i = -1;
// 	while (++i < data->cnt)
// 	{
// 		 if (pipe(cur_pipe) == -1)
// 			error_pipe();
// 		id = fork();
// 		if (id == 0)
// 			child(&data[i], cur_pipe);
// 		else if (id > 0)
// 		{
// 			close(cur_pipe[1]);
// 			dup2(cur_pipe[0], 0);
// 			close(cur_pipe[0]);
// 		}
// 		else
// 			error_fork();
// 		id = fork();
// 		if (id == 0)
// 		{
// 			dup2(data->input_fd, 0);
// 		}
// 	}
// 	for (int i = 0 ; i < data->cnt ; i++)
// 	{
// 		waitpid(-1, NULL, 0);
// 	}
// }

// void	child(t_mini *data, int *cur_pipe)
// {
// 	//ft_putnbr_fd(data->node_id,2);
// 	//ft_putnbr_fd(data->cnt - 1,2);
// 	if (data->node_id == 0)
// 	{
// 		head_process(data, cur_pipe);
// 	}
// 	else if (data->node_id == data->cnt - 1)
// 	{
// 		tail_process(data, cur_pipe);
// 	}
// 	// else
// 	// 	//middle_process();
// }

// void	head_process(t_mini *data, int *cur_pipe)
// {
// 	if (data->input_fd && data->cnt > 1)
// 	{
// 		dup2(data->input_fd, 0);
// 		close(data->input_fd);
// 		close(cur_pipe[0]);
// 		dup2(cur_pipe[1], 1);
// 		close(cur_pipe[1]);
// 	}
// 	cmd_find_start(data);
// }

// void	tail_process(t_mini *data, int *cur_pipe)
// {
// 	if (data->output_fd)
// 	{
// 		dup2(data->output_fd, 1);
// 		close(data->output_fd);
// 		close(cur_pipe[0]);
// 		close(cur_pipe[1]);


// 	}
// 	cmd_find_start(data);
// }

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
	if (data->input_fd != 0)
		close(data->input_fd);
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
		close(data->input_fd);
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

void    error_file(void)
{
	perror("file");
	exit(128);
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

int is_redirection(char *str)
{
	// < > >> <>(?)
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (2);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (3);
	// else if (ft_strncmp(str, "<>", ft_strlen(str)) == 0)
	// 	return (4);
	return (0);
}