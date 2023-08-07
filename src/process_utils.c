/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:45:27 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:45:41 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_realoc(t_mini *data)
{
	int		i;
	int		j;
	int		token_cnt;
	char	**new_token;

	i = -1;
	token_cnt = 0;
	if (data)
	{
		if (data->command)
		{
			while (++i < data->cmd_size)
			{
				if (data->command[i])
				{
					token_cnt++;
				}
			}
		}
	}
	else if (!data || !data->command) 
		return (NULL);
	new_token = (char **)malloc(sizeof(char *) * (token_cnt + 1));
	if (!new_token)
		error_malloc();
	new_token[token_cnt] = NULL;
	i = -1;
	j = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i])
			new_token[++j] = ft_strdup(data->command[i]);
	}
	return (new_token);
}
