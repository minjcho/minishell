/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:15:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:19:51 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_mini *data, t_env *env)
{
	if ((data->cmd_size - data->delete) == 1)
		export_print(env);
	else if ((data->cmd_size - data->delete) > 1)
		export_val(data, env);
}

void	export_val(t_mini *data, t_env *env)
{
	int		i;
	char	*key;
	char	*value;
	char	**temp;
	char	**cmd;

	i = 0;
	key = NULL;
	value = NULL;
	cmd = cmd_realoc(data);
	while (cmd[++i])
	{
		temp = ft_split(cmd[i], '=');
		key = temp[0];
		value = temp[1];
		if (!export_valid_check(key))
			continue;
		if (!value)
			ft_setexport(key, value, env);
		else
		{
			ft_setexport(key, value, env);
			ft_setenv(key, value, env);
		}
		command_free(temp);
	}
	command_free(cmd);
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
			if (key[i] <= 47 || key[i] >= 123 || (key[i] >= 58 && key[i] <= 64) || \
			(key[i] >= 91 && key[i] <= 94) || key[i] == 96)
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
	char    	*k1;
	char	    *k2;
	t_env_node	temp;

	i = -1;
	while (env->export[++i].key)
	{
		j = i + 1;
		while (env->export[j].key)
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
			j++;
		}
	}
}
