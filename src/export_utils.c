/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:49:04 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 15:53:58 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setexport(char *key, char *value, t_env *env)
{
	int			i;
	t_env_node	*temp;

	i = -1;
	while (env->export[++i].key)
	{
		if (ft_strcmp(key, env->export[i].key) == 0)
		{
			if (value)
			{
				free(env->export[i].value);
				env->export[i].value = ft_strdup(value);
			}
			return ;
		}
	}
	temp = env->export;
	env->export = realloc_evnode(key, value, temp, 1);
	env_free(temp);
}

char	*ft_getexport(char *key, t_env *env)
{
	int	i;

	i = -1;
	if (env->export)
	{
		while (env->export[++i].key)
		{
			if (ft_strcmp(env->export[i].key, key) == 0)
				return (env->export[i].key);
		}
	}
	return (NULL);
}
