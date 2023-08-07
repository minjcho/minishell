/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:38:56 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:50:48 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*realloc_evnode(char *key, char *value, t_env_node *node, int flag)
{
	// flag 1 => pluse. flag = -1 minus
	int			new_len;
	t_env_node	*new_node;

	new_len = ft_envlen(node) + flag;
	new_node = (t_env_node *)malloc(sizeof(t_env_node) * (new_len + 1));
	if (!new_node)
		error_malloc();
	new_node[new_len].key = NULL;
	if (flag == -1)
		ft_nodecpy(new_node, node, key);
	else
	{
		ft_nodecpy(new_node, node, NULL);
		if (key)
			new_node[new_len - 1].key = ft_strdup(key);
		else
			new_node[new_len - 1].key = NULL;
		if (value)
			new_node[new_len - 1].value = ft_strdup(value);
		else
			new_node[new_len - 1].value = NULL;
	}
	return (new_node);
}

void	ft_nodecpy(t_env_node *new_node, t_env_node *old, char *delete)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = ft_envlen(old);
	while (++i < len)
	{
		if (delete != NULL && ft_strcmp(delete, old[i].key) == 0)
			continue;
		if (old[i].key)
			new_node[j].key = ft_strdup(old[i].key);
		else
			new_node[j].key = NULL;
		if (old[i].value)
			new_node[j].value = ft_strdup(old[i].value);
		else
			new_node[j].value = NULL;
		j++;
	}
}
