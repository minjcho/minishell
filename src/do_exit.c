/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:52:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 16:54:22 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_mini *data)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (++i < data->cmd_size)
	{
		if (data->command[i] && data->command[i + 1])
		{
			if (!str_digit(data->command[i]))
				do_exit2(data->command[i]);
			error_exit2();
			return ;
		}
		else if (data->command[i])
		{
			if (!str_digit(data->command[i]))
				do_exit2(data->command[i]);
			temp = ft_atoi(data->command[i]);
			break ;
		}
	}
	do_exit3(temp, data->cnt);
}

void	do_exit3(int temp, int cnt)
{
	g_signal = temp;
	if (cnt == 1)
		ft_putstr_fd("exit\n", 2);
	exit(temp);
}

int	str_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

void	do_exit2(char *str)
{
	g_signal = 2;
	error_exit(str);
	exit(2);
}
