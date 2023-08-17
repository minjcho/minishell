/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:34:33 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 19:41:34 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_excute(t_mini *data, t_env *env)
{
	int		i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i] != NULL)
		{
			if (execve(data->command[i], cmd_realoc(data), \
			env_tochar(env->node)) == -1)
				break ;
		}
	}
}

void	cmd_start(t_mini *data, char **split_path, t_env *env)
{
	char	*slash_join;
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	while (split_path && split_path[++i])
	{
		slash_join = ft_strjoin(split_path[i], "/");
		j = -1;
		while (++j < data->cmd_size)
		{
			if (data->command[j] != NULL)
			{
				cmd = ft_strjoin(slash_join, data->command[j]);
				if (access(cmd, X_OK) != 0)
					continue ;
				execve(cmd, cmd_realoc(data), env_tochar(env->node));
				free(cmd);
				cmd = NULL;
			}
		}
		free(slash_join);
	}
	error_cmdnotfound(data->command[0]);
}

void	cmd_find(t_mini *data, t_env *env)
{
	char	*temp;
	char	**split_path;

	temp = ft_getenv("PATH", env);
	if (temp)
		split_path = ft_split(temp, ':');
	else
		split_path = NULL;
	first_excute(data, env);
	cmd_start(data, split_path, env);
	command_free(split_path);
}
