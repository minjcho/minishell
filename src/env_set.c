/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:20:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/21 15:04:16 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_init(t_env *env, char **envp)
{
	int	size;

	size = envp_size(envp);
	env->node = malloc(sizeof(t_env_node) * (size + 1));
	if (!env->node)
		error_malloc();
	env->export = malloc(sizeof(t_env_node) * (size + 1));
	if (!env->export)
		error_malloc();
	envp_split(env, envp);
}

void	envp_split(t_env *env, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
			{
				env_substr(env, envp, i, j);
				break ;
			}
		}
	}
}

void	env_substr(t_env *env, char **envp, int i, int j)
{
	env->node[i].key = ft_substr(envp[i], 0, j);
	env->export[i].key = ft_substr(envp[i], 0, j);
	if (envp[i][j + 1])
	{
		env->node[i].value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
		env->export[i].value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
	}
	else
	{
		env->node[i].value = malloc(1);
		if (!env->node[i].value)
			error_malloc();
		env->export[i].value = malloc(1);
		if (!env->export[i].value)
			error_malloc();
	}
}

int	envp_size(char **envp)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (envp[++i])
		len++;
	return (len);
}
