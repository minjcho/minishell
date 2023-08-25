/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:06:49 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 15:36:29 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_g_signal(char **str, int start_idx)
{
	char	*tmp;
	char	*new_str;
	char	*start_ptr;

	tmp = ft_itoa(g_signal);
	start_ptr = ft_strstr(*str + start_idx, "$?");
	if (start_ptr)
	{
		new_str = (char *)malloc(ft_strlen(*str) - \
								ft_strlen("$?") + ft_strlen(tmp) + 1);
		if (!new_str)
			error_malloc();
		ft_strncpy(new_str, *str, start_ptr - *str);
		ft_strcpy(new_str + (start_ptr - *str), tmp);
		ft_strcat(new_str, start_ptr + ft_strlen("$?"));
		free(*str);
		*str = new_str;
	}
	free(tmp);
}

int	count_pipes(char **tmp_command)
{
	int	i;
	int	total_commands;

	i = -1;
	total_commands = 0;
	while (tmp_command[++i])
	{
		if (ft_strcmp(tmp_command[i], "|") == 0)
			total_commands++;
	}
	return (total_commands + 1);
}

void	allocate_and_set_command(t_mini *mini, char **tmp_command, \
									int cmd_count, int start_idx)
{
	int	k;

	mini->command = (char **)malloc((cmd_count + 1) * sizeof(char *));
	if (!mini->command)
		error_malloc();
	k = -1;
	while (++k < cmd_count)
	{
		mini->command[k] = ft_strdup(tmp_command[start_idx + k]);
	}
	mini->command[cmd_count] = NULL;
	mini->cmd_size = cmd_count;
}
