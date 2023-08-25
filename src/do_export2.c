/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:33:02 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 17:23:30 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	export_valid_check2(char *str)
{
	if (*str == '=')
	{
		error_export_valid(str);
		return (0);
	}
	return (1);
}

int	export_valid_check(char *key)
{
	int	i;

	i = -1;
	if (key)
	{
		if (key[0] >= '0' && key[0] <= '9')
		{
			error_export_valid(key);
			return (0);
		}
		while (key[++i])
		{
			if (key[i] == '=')
				break ;
			if (key[i] <= 47 || key[i] >= 123 || (key[i] >= 58 && \
			key[i] <= 60) || \
			(key[i] >= 91 && key[i] <= 94) || key[i] == 96 \
			|| (key[i] >= 62 && key[i] <= 64))
			{
				error_export_valid(key);
				return (0);
			}
		}
	}
	return (1);
}

void	export_print(t_env *env)
{
	int		i;
	char	*temp;

	i = -1;
	temp = "declare -x ";
	if (env->export)
	{
		export_sorting(env);
		while (env->export[++i].key)
		{
			write(1, temp, ft_strlen(temp));
			write(1, env->export[i].key, ft_strlen(env->export[i].key));
			if (env->export[i].value)
			{
				write(1, "=\"", 2);
				write(1, env->export[i].value, ft_strlen(env->export[i].value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
	}
}

void	export_sorting(t_env *env)
{
	int			i;
	int			j;
	char		*k1;
	char		*k2;
	t_env_node	temp;

	i = -1;
	while (env->export[++i].key)
	{
		j = i;
		while (env->export[++j].key)
		{
			k1 = env->export[i].key;
			k2 = env->export[j].key;
			if (ft_strncmp(k1, k2, ft_strlen(k1)) > 0)
			{
				temp.key = k1;
				temp.value = env->export[i].value;
				env->export[i].key = env->export[j].key;
				env->export[i].value = env->export[j].value;
				env->export[j].key = temp.key;
				env->export[j].value = temp.value;
			}
		}
	}
}
