/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:29:20 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 15:56:25 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(char **command)
{
	int		i;
	char	*temp;
	char	**temp2;

	i = -1;
	if (command)
	{
		temp2 = command;
		while (command[++i])
		{
			temp = command[i];
			command[i] = NULL;
			free(temp);
		}
		command = NULL;
		free(temp2);
	}
}

void	env_free(t_env_node *node)
{
	int	i;

	i = -1;
	if (node)
	{
		while (node[++i].key)
		{
			free(node[i].key);
			free(node[i].value);
		}
		free(node);
	}
}

void	node_free(t_mini *node)
{
	int		i;
	t_mini	*temp;

	i = -1;
	if (node)
	{
		temp = node;
		while (++i < node->cnt)
		{
			if (&node[i])
				command_free(node[i].command);
		}
		node = NULL;
		free(temp);
	}
}
