/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:08:52 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/23 13:09:19 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_single_env(char **command, t_env *env)
{
	char	*env_value;

	if ((*command)[0] == '$' && (*command)[1] != '?' && (*command)[1])
	{
		env_value = ft_getenv((*command) + 1, env);
		if (env_value)
		{
			free(*command);
			*command = ft_strdup(env_value);
		}
		else
		{
			free(*command);
			*command = ft_strdup("");
		}
	}
}

void	replace_env(t_mini *mini, t_env *env)
{
	int		idx;
	int		jdx;

	idx = -1;
	while (mini[++idx].command)
	{
		jdx = -1;
		while (++jdx < mini[idx].cmd_size)
			replace_single_env(&(mini[idx].command[jdx]), env);
	}
	remove_double_quotation(mini, env);
	remove_single_quotation(mini);
}
