/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:20:28 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:20:41 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_env(t_env *env)
{
	int		i;
	char	*k_temp;
	char	*v_temp;

	i = -1;
	if (env->node)
	{
		while (env->node[++i].key)
		{
			k_temp = env->node[i].key;
			v_temp = env->node[i].value;
			write(1, k_temp, ft_strlen(k_temp));
			write(1, "=", 1);
			write(1, v_temp, ft_strlen(v_temp));
			write(1, "\n", 1);
		}
	}
}