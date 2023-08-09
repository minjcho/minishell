/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:35:31 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/08 16:06:57 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(char *key, char *value, t_env *env)
{
	int			i;
	t_env_node	*temp;

	i = -1;
	while (env->node[++i].key)
	{
		if (ft_strcmp(key, env->node[i].key) == 0)
		{
			if (value)
			{
				free(env->node[i].value);
				env->node[i].value = ft_strdup(value);
			}
			return ;
		}
	}
	temp = env->node;
	env->node = realloc_evnode(key, value, temp, 1);
	env_free(temp);
}

char	*ft_getenv(char *key, t_env *env)
{
	int	i;

	i = -1;
	if (env->node)
	{
		while (env->node[++i].key)
		{
			if (ft_strcmp(key, env->node[i].key) == 0)
			{
				return (env->node[i].value);
			}
		}
	}
	return (NULL);
}

int	ft_envlen(t_env_node *node)
{
	int			i;
	int			cnt;

	i = -1;
	cnt = 0;
	if (node->key)
	{
		while (node[++i].key)
			cnt++;
	}
	return (cnt);
}

char	**env_tochar(t_env_node *env)
{
	int		i;
	int		size;
	char	*equal_sign;
	char	*origin_envstr;	
	char	**ret;

	i = -1;
	ret = NULL;
	size = 0;
	if (env)
		size = ft_envlen(env);
	if (size)
	{
		ret = (char **)malloc(sizeof(char *) * (size + 1));
		if (!ret)
			error_malloc();
		while (++i < size)
		{
			if (env[i].key)
				equal_sign = ft_strjoin(env[i].key, "=");
			else
				equal_sign = NULL;
			if (env[i].value)
				origin_envstr = ft_strjoin(equal_sign, env[i].value);
			else
				origin_envstr = ft_strdup(equal_sign);
			ret[i] = origin_envstr;
			// ft_putstr_fd(ret[i], 2);
			// ft_putstr_fd("\n", 2);
			free(equal_sign);
			origin_envstr = NULL;
		}
	}
	return (ret);
}