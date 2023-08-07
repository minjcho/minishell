/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:47:56 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:48:18 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(t_mini *data)
{
	int		option_idx;
	char	*new_line;
	int		temp;
	int		i;

	i = 0;
	// if (data->output_fd)
	// 	temp = data->output_fd;
	// else 
		temp = 1;
	option_idx = is_echo_option(data);
	if (option_idx > 1)
	{
		while (option_idx < data->cmd_size)
		{
			write(temp, data->command[option_idx], \
			ft_strlen(data->command[option_idx]));
			write(temp, " ", 1);
			option_idx++;
		}
	}
	else
	{
		while (option_idx < data->cmd_size)
		{
			write(temp, data->command[option_idx], \
			ft_strlen(data->command[option_idx]));
			write(temp, " ", 1);
			option_idx++;
		}
		write(temp, "\n", 1);
	}
}

int	is_echo_option(t_mini *data)
{
	int	i;
	int	j;

	i = 0;
	while(data->command[++i])
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