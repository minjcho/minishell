/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:41:21 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/09 10:20:48 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_ready2(t_mini *data, t_env *env);

void	exec_cmd(t_mini *data, t_env *env)
{
	int	i;

	i = -1;
	heredoc_ready(data, env);
	//heredoc_ready2(data, env);
	while (++i < data->cnt)
	{
		redirection_ready(&data[i]);
	}
	builtin_counter(data);
	if (data->builtin_cnt == 1 && data->cnt == 1)
	{
		if (data->input_fd)
		{
			dup2(data->input_fd, 0);
			close(data->input_fd);
		}
		if (data->output_fd)
		{
			dup2(data->output_fd, 1);
			close(data->output_fd);
		}
		do_builtin(data, env);
		dup2(data->origin_in, 0);
		dup2(data->origin_out, 1);
		return ;
	}
	process_start2(data, env);
}

// int	is_redirection2(char *str)
// {
// 	if (ft_strcmp(str, "<") == 0)
// 		return (1);
// 	else if (ft_strcmp(str, ">") == 0)
// 		return (2);
// 	else if (ft_strcmp(str, ">>") == 0)
// 		return (4);
// 	else if (ft_strcmp(str, "<<") == 0)
// 		return (3);
// 	return (0);
// }

// void	redirection_set(t_mini *data, t_env *env) // &data[i];
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->cmd_size)
// 	{
// 		if (data->command[i])
// 		{
// 			if (is_redirection2(data->command[i]) == 1)
// 				red_left(data, env, i);
// 			else if (is_redirection2(data->command[i]) == 2)
// 				red_right(data, env, i);
// 			else if (is_redirection2(data->command[i]) == 3)
// 				heredoc_left(data, env, i);
// 			else if (is_redirection2(data->command[i]) == 4)
// 				heredoc_right(data, env, i);
// 		}
// 	}
// }

// void	heredoc_right(t_mini *data, t_env *env, int i)
// {
// 	int	fd;

// 	(void)env;
// 	fd = open(data->command[i + 1],  O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 		error_file();
// 	set_cmd_null(data, i, i + 1);
// 	dup2(fd, 1);
// 	close(fd);
// }

// void	heredoc_left(t_mini *data, t_env *env, int i)
// {
// 	char	*limiter;
// 	char	*str;
// 	int		fd[2];
// 	pid_t	id;

// 	(void)env;
// 	limiter = ft_strdup(data->command[i + 1]);
// 	set_cmd_null(data, i, i + 1);
// 	pipe(fd);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fd[0]);
// 		while (1)
// 		{
// 			str = readline("> ");
// 			if (!str || ft_strcmp(str, limiter) == 0)
// 				break;
// 			write(fd[1], str, ft_strlen(str));
// 			write(fd[1], "\n", 1);
// 			free(str);
// 		}
// 		close(fd[1]);
// 		exit(0);
// 	}
// 	else if (id > 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], 0);
// 		close(fd[0]);
// 		free(limiter);
// 	}
// 	else
// 		error_fork();
// 	wait(NULL);
// }

// void	red_right(t_mini *data, t_env *env, int i)
// {
// 	int	fd;

// 	(void)env;
// 	fd = open(data->command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644 );
// 	if (fd == -1)
// 		error_file();
// 	set_cmd_null(data, i, i + 1);
// 	dup2(fd, 1);
// 	close(fd);
// }

// void	red_left(t_mini *data, t_env *env, int i)
// {
// 	int	fd;

// 	fd = 0;
// 	(void)env;
// 	fd = open(data->command[i + 1], O_RDONLY);
// 	if (fd == -1)
// 		error_file(); // error ?
// 	set_cmd_null(data, i, i + 1);
// 	dup2(fd, 0);
// 	close(fd);
// }

// void	exec_cmd(t_mini *data, t_env *env)
// {
// 	int	i;
// 	int	prev_pipe;

// 	i = -1;
// 	(void)env;
// 	prev_pipe = 0;
// 	while (++i < data->cnt)
// 	{
// 		int		cur_pipe[2];
// 		pid_t	id1;

// 		pipe(cur_pipe);
// 		id1 = fork();
// 		if (id1 == 0)
// 		{
// 			redirection_set(&data[i], env);
// 			if (data[i].cnt > 1 && prev_pipe)
// 			{
// 				dup2(prev_pipe, 0);
// 				close(prev_pipe);
// 			}
// 			else if (data[i].cnt > 1 && data[i].cnt - 1 != i)
// 			{
// 				close(cur_pipe[0]);
// 				dup2(cur_pipe[1], 1);
// 				close(cur_pipe[1]);
// 			}
// 			if (!data[i].builtin_cnt)
// 				cmd_find(&data[i], env);
// 			else if (data[i].builtin_cnt == 1)
// 				do_builtin(&data[i], env);
// 		}
// 		else if(id1 > 0)
// 		{
// 			close(cur_pipe[1]);
// 			if (prev_pipe)
// 				close(prev_pipe);
// 			if (data[i].cnt > 1)
// 				prev_pipe = cur_pipe[0];
// 			else
// 				close(cur_pipe[0]);
// 		}
// 	}
// 	int	j;
// 	j = -1;
// 	while (++j < i)
// 		wait(NULL);
// }

// void	heredoc_ready2(t_mini *data, t_env *env)
// {
// 	int		fd[2];
// 	pid_t	id;

// 	pipe(fd);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		int		i;
// 		char	*str;

// 		i = 0;
// 		str = NULL;
// 		while (1)
// 		{
// 			str = readline("> ");
// 			if (str == NULL)
// 				break;
// 			write(fd[1], str, ft_strlen(str));
// 			free(str);
// 		}
// 	}
// 	else if (id > 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], 0);
// 		close(fd[0]);
// 		wait(NULL);
// 	}
// 	else
// 		error_fork();
// }

void	first_excute(t_mini *data, t_env *env)
{
	int		i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i] != NULL)
			execve(data->command[i], cmd_realoc(data), env_tochar(env->node));
	}
}

void	cmd_start(t_mini *data, char **split_path, t_env *env)
{
	char	*slash_join;
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	(void)env;
	while (split_path && split_path[++i])
	{
		slash_join = ft_strjoin(split_path[i], "/");
		j = -1;
		while (++j < data->cmd_size)
		{
			if (data->command[j] != NULL)
			{
				cmd = ft_strjoin(slash_join, data->command[j]);
				execve(cmd, cmd_realoc(data), NULL);
				free(cmd);
			}
		}
		free(slash_join);
	}
	error_cmdnotfound(data->command[0], data);
}

void	cmd_find(t_mini *data, t_env *env)
{
	char	*temp;
	char	**split_path;
	
	temp = ft_getenv("PATH", env);
	if (temp)
		split_path = ft_split(temp, ':');
	else
		split_path = NULL;
	first_excute(data, env);
	cmd_start(data, split_path, env);
	command_free(split_path);
}