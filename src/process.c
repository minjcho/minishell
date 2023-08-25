/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:41:21 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 17:56:20 by jinhyeok         ###   ########.fr       */
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
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
		if (set_re_and_pipe(data, env, cur_pipe, i))
			continue ;
		else if (data[i].is_signal)
			break ;
		pipe(cur_pipe);
		p.data = data;
		p.env = env;
		p.i = i;
		exec_fork(&p, cur_pipe);
		origin_dup(data, i);
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
	else
		close(cur_pipe[0]);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
