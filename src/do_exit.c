/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:52:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/10 17:58:23 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_mini *data)
{
	int	i;
	int	j;
	int	temp;

	i = -1;
	temp = 0;
	while (i++ < data->cmd_size)
	{
		j = 0;
		if (data->command[i] && data->command[i + 1])
		{
			while (data->command[i + 1][j])
			{
				if (!ft_isdigit(data->command[i + 1][j]))
					do_exit2(data->command[i + 1]);
				j++;
			}
			temp = ft_atoi(data->command[i + 1]);
			break;
		}
	}
	global_signal = temp;
	exit(temp);
}

void	do_exit2(char * str)
{
	global_signal = 255;
	error_exit(str);
	exit(255);
}