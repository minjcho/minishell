/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ready.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:13:22 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:25:55 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_counter(t_mini *data)
{
	int	i;
	int	builtin_cnt;

	i = -1;
	builtin_cnt = 0;
	while (++i < data->cnt)
	{
		builtin_cnt = 0;
		if (builtin_check(&data[i]))
			builtin_cnt++;
		data[i].builtin_cnt = builtin_cnt;
	}
}

int	builtin_check(t_mini *data)
{
	char	*temp;

	if (data->command[0])
	{
		temp = data->command[0];
		if (ft_strcmp(temp, "cd") == 0)
			return (1);
		else if (ft_strcmp(temp, "echo") == 0)
			return (2);
		else if (ft_strcmp(temp, "pwd") == 0)
			return (3);
		else if (ft_strcmp(temp, "export") == 0)
			return (4);
		else if (ft_strcmp(temp, "unset") == 0)
			return (5);
		else if (ft_strcmp(temp, "env") == 0)
			return (6);
		else if (ft_strcmp(temp, "exit") == 0)
			return (7);
	}
	return (0);
}

void	do_builtin(t_mini *data, t_env *env)
{
	if (builtin_check(data) == 1)
		do_cd(data, env);
	else if (builtin_check(data) == 2)
		do_echo(data);
	else if (builtin_check(data) == 3)
		do_pwd(data, env);
	else if (builtin_check(data) == 4)
		do_export(data, env);
	else if (builtin_check(data) == 5)
		do_unset(data, env);
	else if (builtin_check(data) == 6)
		do_env(env);
	else if (builtin_check(data) == 7)
		do_exit(data);
}
