/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:41:21 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 20:20:32 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe_close(t_params *p, int *cur_pipe)
{
	if (p->data[p->i].cnt > 1 && p->prev_pipe && !p->data[p->i].is_heredoc)
	{
		dup2(p->prev_pipe, 0);
		close(p->prev_pipe);
	}
	if (p->data[p->i].cnt > 1 && p->data[p->i].cnt - 1 != p->i && \
	!p->data[p->i].output_fd)
	{
		close(cur_pipe[0]);
		dup2(cur_pipe[1], 1);
		close(cur_pipe[1]);
	}
	else
	{
		close(cur_pipe[0]);
		close(cur_pipe[1]);
	}
}

void	exec_fork(t_params *p, int *cur_pipe)
{
	pid_t	id1;

	id1 = fork();
	if (id1 == 0)
	{
		handle_pipe_close(p, cur_pipe);
		child_execve(p->data, p->env, p->i);
	}
	else if (id1 > 0)
		parent_set(p->data, cur_pipe, &p->prev_pipe, p->i);
	else
		error_fork();
}

void	exec_cmd(t_mini *data, t_env *env)
{
	int			i;
	t_params	p;
	int			cur_pipe[2];

	i = -1;
	p.prev_pipe = 0;
	if (only_builtin(data, env))
		return ;
	while (++i < data->cnt)
	{
		redirection_set(&data[i], env);
		pipe(cur_pipe);
		p.data = data;
		p.env = env;
		p.i = i;
		exec_fork(&p, cur_pipe);
	}
	ft_wait(i);
}

void	child_execve(t_mini *data, t_env *env, int i)
{
	if (!data[i].builtin_cnt && (data[i].cmd_size - data[i].delete) > 0)
		cmd_find(&data[i], env);
	else if (data[i].builtin_cnt == 1)
		do_builtin(&data[i], env);
	exit(0);
}

void	parent_set(t_mini *data, int *cur_pipe, int *prev_pipe, int i)
{
	close(cur_pipe[1]);
	if (*prev_pipe)
		close(*prev_pipe);
	if (data[i].cnt > 1)
		*prev_pipe = cur_pipe[0];
}

// void	exec_cmd(t_mini *data, t_env *env)
// {
// 	int	i;
// 	int	prev_pipe;

// 	i = -1;
// 	prev_pipe = 0;
// 	if (only_builtin(data, env))
// 		return ;
// 	while (++i < data->cnt)
// 	{
// 		int		cur_pipe[2];
// 		pid_t	id1;

// 		redirection_set(&data[i], env);
// 		pipe(cur_pipe);
// 		id1 = fork();
// 		if (id1 == 0)
// 		{
// 			if (data[i].cnt > 1 && prev_pipe && !data[i].is_heredoc)
// 			{
// 				dup2(prev_pipe, 0);
// 				close(prev_pipe);
// 			}
// 			if (data[i].cnt > 1 && data[i].cnt - 1 != i && 
// 			!data[i].output_fd)
// 			{
// 				close(cur_pipe[0]);
// 				dup2(cur_pipe[1], 1);
// 				close(cur_pipe[1]);
// 			}
// 			else
// 			{
// 				close(cur_pipe[0]);
// 				close(cur_pipe[1]);
// 			}
// 			child_execve(data, env, i);
// 		}
// 		else if(id1 > 0)
// 			parentset(data, cur_pipe, &prev_pipe, i);
// 		else
// 			error_fork();
// 	}
// 	ft_wait(i);
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

// void	exec_cmd(t_mini *data, t_env *env)
// {
// 	int	i;

// 	i = -1;
// 	heredoc_ready(data, env);
// 	//heredoc_ready2(data, env);
// 	while (++i < data->cnt)
// 	{
// 		redirection_ready(&data[i]);
// 	}
// 	builtin_counter(data);
// 	if (data->builtin_cnt == 1 && data->cnt == 1)
// 	{
// 		if (data->input_fd)
// 		{
// 			dup2(data->input_fd, 0);
// 			close(data->input_fd);
// 		}
// 		if (data->output_fd)
// 		{
// 			dup2(data->output_fd, 1);
// 			close(data->output_fd);
// 		}
// 		do_builtin(data, env);
// 		dup2(data->origin_in, 0);
// 		dup2(data->origin_out, 1);
// 		return ;
// 	}
// 	process_start2(data, env);
// }

// void	heredoc_read(char *limiter, int *fd, t_env *env)
// {
// 	char	*str;
// 	//char	**temp;

// 	while (1)
// 	{
// 		str = readline("> ");
// 		if (!str || ft_strcmp(str, limiter) == 0)
// 		{
// 			free(limiter);
// 			free(str);
// 			close(fd[1]);
// 			exit(0);
// 		}
// 		if (dollar_counter(str))
// 		{
// 			int	i;

// 			i = -1;
// 			while (str[++i])
// 			{
// 				if (str[i] == '$')
// 				{
// 					if (str[i + 1] == ' ' || str[i + 1] == '\0')
// 						write(fd[1], &str[i], 1);
// 					else if (str[i + 1])
// 					{
// 						int		j;
// 						char	*environ;
// 						char	*env_val;

// 						j = i + 1;
// 						while (str[j])
// 						{
// 							if (str[j] == ' ' || !str[j] || str[j] == '$')
// 								break;
// 							j++;
// 						}
// 						j--;
// 						environ = ft_substr(str, i + 1, j);
// 						env_val = ft_getenv(environ, env);
// 						write(fd[1], env_val, ft_strlen(env_val));
// 						i += j;
// 						free(environ);
// 					}
// 				}
// 				else
// 					write(fd[1], &str[i], 1);
// 			}
// 			write(fd[1], "\n", 1);
// 		}
// 		else
// 		{
// 			//set normal
// 			write(fd[1], str, ft_strlen(str));
// 			write(fd[1], "\n", 1);
// 		}
// 		free(str);
// 	}
// }

// void	heredoc_read(char *limiter, int *fd, t_env *env)
// {
// 	char	*str;

// 	while (1)
// 	{
// 		str = readline("> ");
// 		if (!str || ft_strcmp(str, limiter) == 0)
// 		{
// 			free(limiter);
// 			free(str);
// 			close(fd[1]);
// 			exit(0);
// 		}
// 		if (dollar_counter(str))
// 			dollor_conver(str, fd, env);
// 		else
// 		{
// 			//set normal
// 			write(fd[1], str, ft_strlen(str));
// 			write(fd[1], "\n", 1);
// 		}
// 		free(str);
// 	}
// }

// int	dollar_counter(char *str)
// {
// 	int	i;
// 	int	cnt;

// 	i = 0;
// 	cnt = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			cnt++;
// 		i++;
// 	}
// 	return (cnt);
// }

// char	**dollar_check(char **str)
// {
// 	int		i;
// 	char	**ret;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (is_dollar(str[i]))
// 			split_token(str, i);
// 	}
// }

// void	split_token(char **str, int i)
// {
// 	char *temp;
// 	char	**split;
// 	int	i;

// 	temp = str[i];
// 	i = -1;
// 	split = ft_split(str[i]);
// 	free(temp);
// }

// int	is_dollar(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			if (str[i + 1] && str[i + 1] != ' ')
// 				return (1);
// 		}
// 	}
// 	return (0);
// }
