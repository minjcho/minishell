/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:13:21 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 10:19:25 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_red(pid_t id, int *fd, t_mini *data)
{
	int	status;

	status = 0;
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(id, &status, 0);
	signal_heredoc(data, status);
}

void	signal_heredoc(t_mini *data, int status)
{
	int	pi[2];

	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			pipe(pi);
			close(0);
			close(pi[1]);
			dup2(pi[0], 0);
			close(pi[0]);
			ft_putstr_fd("\n", 2);
			g_signal = 130;
			data->is_signal = 1;
		}
	}
}

void	sigint_handler(int signal)
{
	(void)signal;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_main(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
