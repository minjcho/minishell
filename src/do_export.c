/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:15:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 14:33:38 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_mini *data, t_env *env)
{
	if ((data->cmd_size - data->delete) == 1)
		export_print(env);
	else if ((data->cmd_size - data->delete) > 1)
		export_val2(data, env);
}

// void	export_val(t_mini *data, t_env *env)
// {
// 	int		i;
// 	char	*key;
// 	char	*value;
// 	char	**temp;
// 	char	**cmd;

// 	i = 0;
// 	key = NULL;
// 	value = NULL;
// 	cmd = cmd_realoc(data);
// 	while (cmd[++i])
// 	{
// 		temp = ft_split(cmd[i], '=');
// 		key = temp[0];
// 		value = temp[1];
// 		if (!export_valid_check2(cmd[i]) || !export_valid_check(key))
// 		{
// 			command_free(temp);
// 			continue;
// 		}
// 		if (!value)
// 			ft_setexport(key, value, env);
// 		else
// 		{
// 			ft_setexport(key, value, env);
// 			ft_setenv(key, value, env);
// 		}
// 		command_free(temp);
// 	}
// 	command_free(cmd);
// }

void	export_val2(t_mini *data, t_env *env)
{
	int		i;
	char	**temp;
	char	**cmd;
	char	*temp1;

	i = 0;
	cmd = cmd_realoc(data);
	while (cmd[++i])
	{
		if (!export_valid_check2(cmd[i]) || !export_valid_check(cmd[i]))
			continue ;
		temp = ft_split(cmd[i], '=');
		if (!is_equal(cmd[i]))
			ft_setexport(cmd[i], NULL, env);
		else if (equal_checker(cmd[i]))
		{
			temp1 = malloc(1);
			set_export_env(temp[0], temp1, env);
			free(temp1);
		}
		else if (is_equal(cmd[i]) && !equal_checker(cmd[i]))
			set_export_env(temp[0], temp[1], env);
		command_free(temp);
	}
	command_free(cmd);
}

void	set_export_env(char *key, char *value, t_env *env)
{
	ft_setexport(key, value, env);
	ft_setenv(key, value, env);
}

int	equal_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=' && !str[i + 1])
			return (1);
	}
	return (0);
}
