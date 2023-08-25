/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:00:55 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 16:35:23 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_set(t_mini *data, t_env *env)
{
	int	i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i])
		{
			if (is_redirection2(data->command[i]) == 1)
			{
				data->is_heredoc = 1;
				red_left(data, i);
			}
			else if (is_redirection2(data->command[i]) == 2)
				red_right(data, i);
			else if (is_redirection2(data->command[i]) == 3)
			{
				dup2(data->origin_in, 0);
				dup2(data->origin_out, 1);
				data->is_heredoc = 1;
				heredoc_left(data, env, i);
			}
			else if (is_redirection2(data->command[i]) == 4)
				heredoc_right(data, i);
		}
	}
}

void	heredoc_right(t_mini *data, int i)
{
	int	fd;

	fd = open(data->command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error_file(data->command[i + 1]);
	data->output_fd = fd;
	set_cmd_null(data, i, i + 1);
	dup2(fd, 1);
	close(fd);
}

void	heredoc_left(t_mini *data, t_env *env, int i)
{
	char	*limiter;
	int		fd[2];
	pid_t	id;

	limiter = ft_strdup(data->command[i + 1]);
	set_cmd_null(data, i, i + 1);
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		heredoc_read(limiter, fd, env);
	}
	else if (id > 0)
	{
		heredoc_signal_red(id, fd, data);
		free(limiter);
	}
	else
		error_fork();
}

void	red_right(t_mini *data, int i)
{
	int	fd;

	fd = 0;
	if (data->input_fd != -1)
		fd = open(data->command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && data->echo_fail == 0)
		error_file(data->command[i + 1]);
	data->output_fd = fd;
	if (fd == -1 && data->echo_fail == 0)
		data->echo_fail = 1;
	set_cmd_null(data, i, i + 1);
	dup2(fd, 1);
	close(fd);
}

void	red_left(t_mini *data, int i)
{
	int	fd;

	fd = 0;
	fd = open(data->command[i + 1], O_RDONLY);
	if (fd == -1 && data->echo_fail == 0)
		error_file(data->command[i + 1]);
	data->input_fd = fd;
	if (fd == -1 && data->echo_fail == 0)
		data->echo_fail = 1;
	set_cmd_null(data, i, i + 1);
	dup2(fd, 0);
	close(fd);
}
