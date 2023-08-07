/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:32:07 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:34:06 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cd(t_mini *data, t_env *env)
{
	int	i;

	i = 0;
	while (++i < data->cmd_size)
	{
		if (data->command[i])
		{
			if (ft_strcmp(data->command[i], "~") == 0)
				home_directory(env);
			else if (ft_strcmp(data->command[i], "-") == 0)
				back_directory(env);
			else
				goto_directory(ft_strdup(data->command[i]), env);
			return;
		}
	}
	home_directory(env);
}

void	goto_directory(char *target, t_env *env)
{
	char	cur_directory[256];

	if (getcwd(cur_directory, sizeof(cur_directory)))
		ft_setenv("OLDPWD", cur_directory, env);
	if (chdir(target) == -1)
	{
		perror(target);
		free(target);
		return ;
	}
	ft_memset(cur_directory, 0, sizeof(cur_directory));
	if (getcwd(cur_directory, sizeof(cur_directory)))
		ft_setenv("PWD", cur_directory, env);
	free (target);
}

void	back_directory(t_env *env)
{
	char	*target;
	char	*temp;

	temp = ft_getenv("OLDPWD", env);
	if (!temp)
	{
		perror("path");
		return ;
	}
	target = ft_strdup(temp);
	goto_directory(target, env);
}

void	home_directory(t_env *env)
{
	char *target;
	char *temp;

	temp = ft_getenv("HOME", env);
	if (!temp)
	{
		perror("HOME");
		return ;
	}
	target = ft_strdup(temp);
	goto_directory(target, env);
}

// int	to_back_directory(char *to_directory)
// {
// 	if (ft_strcmp(to_directory, "-") == 0)
// 		return (1);
// 	else
// 		return (0);
// }

// int	to_home_directory(char *to_directory)
// {
// 	if (!to_directory)
// 		return (1);
// 	if (!ft_strcmp(to_directory, "~"))
// 		return (1);
// 	return (0);
// }
