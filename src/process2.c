/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:55:04 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 17:56:59 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_re_and_pipe(t_mini *data, t_env *env, int *cur_pipe, int i)
{
	redirection_set(&data[i], env);
	if (data[i].input_fd == -1)
	{
		control_pipe(cur_pipe);
		return (1);
	}
	return (0);
}

void	control_pipe(int *cur_pipe)
{
	pipe(cur_pipe);
	close(cur_pipe[1]);
	dup2(cur_pipe[0], 0);
	close(cur_pipe[0]);
}
