/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:47:56 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 14:21:45 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(t_mini *data)
{
	int		option_idx;
	int		i;

	i = 0;
	option_idx = is_echo_option(data);
	if (option_idx > 1)
	{
		while (option_idx < data->cmd_size)
		{
			echo_write(data, option_idx);
			option_idx++;
		}
	}
	else
	{
		while (option_idx < data->cmd_size)
		{
			echo_write(data, option_idx);
			option_idx++;
		}
		write(1, "\n", 1);
	}
}

void	echo_write(t_mini *data, int option_idx)
{
	if (data->command[option_idx] && \
	ft_strcmp("$?", data->command[option_idx]) == 0)
	{
		ft_putnbr_fd(global_signal, 1);
		global_signal = 0;
		write(1, " ", 1);
		option_idx++;
	}
	write(1, data->command[option_idx], \
	ft_strlen(data->command[option_idx]));
	write(1, " ", 1);
}

int	is_echo_option(t_mini *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->command[++i])
	{
		j = 0;
		if (data->command[i][j] == '-')
		{
			while (data->command[i][++j])
			{
				if (data->command[i][j] != 'n')
					return (i);
			}
		}
		else
			return (i);
	}
	return (i);
}
