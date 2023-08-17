/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:45:27 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 19:34:02 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_realoc(t_mini *data)
{
	int		i;
	int		j;
	int		token_cnt;
	char	**new_token;

	token_cnt = token_counter(data);
	if (!data || !data->command)
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

int	token_counter(t_mini *data)
{
	int	i;
	int	token_cnt;

	i = -1;
	token_cnt = 0;
	if (data)
	{
		if (data->command)
		{
			while (++i < data->cmd_size)
			{
				if (data->command[i])
					token_cnt++;
			}
		}
	}
	return (token_cnt);
}

int	is_redirection2(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, ">>") == 0)
		return (4);
	else if (ft_strcmp(str, "<<") == 0)
		return (3);
	return (0);
}

void	ft_wait(int n)
{
	int	status;
	int	i;

	i = -1;
	while (++i < n)
		waitpid(-1, &status, 0);
	global_signal = WEXITSTATUS(status);
}
