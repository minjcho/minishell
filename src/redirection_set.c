/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:00:55 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:12:26 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_ready(t_mini *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i] && is_redirection(data->command[i]))
		{
			set_redirection(data, i);
		}
	}
	return (0);
}

void	set_redirection(t_mini *data, int i)
{
	if (!data->command[i])
		return ;
	if (is_redirection(data->command[i]) == 1)
		file_open(data, i);
	else if (is_redirection(data->command[i]) == 2)
		file_create(data, i, 0);
	else if (is_redirection(data->command[i]) == 3)
		file_create(data, i, 1);
}

int	is_redirection(char *str)
{
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (2);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (3);
	return (0);
}
