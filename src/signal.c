/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:13:21 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/24 16:48:24 by minjcho          ###   ########.fr       */
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
			g_signal = 1;
			data->is_signal = 1;
		}
	}
}

void	sigint_handler(int signal)
{
	struct termios	new_term;
	struct termios	temp;

	(void)signal;
	g_signal = 1;
	tcgetattr(STDIN_FILENO, &new_term);
	tcgetattr(STDIN_FILENO, &temp);
	new_term.c_lflag &= ~(ICANON | ECHO | ECHOCTL);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	tcsetattr(STDIN_FILENO, TCSANOW, &temp);
}

void	signal_main(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
