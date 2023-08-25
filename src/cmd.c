/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:34:33 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 15:32:10 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

void	first_excute(t_mini *data, t_env *env)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (++i < data->cmd_size)
	{
		if (data->command[i] != NULL)
		{
			flag = is_slash(data->command[i]);
			if (execve(data->command[i], cmd_realoc(data), \
			env_tochar(env->node)) == -1)
			{
				if (flag)
					error_cmdnotfound(data->command[i]);
				break ;
			}
		}
	}
}

void	cmd_start(t_mini *data, char **split_path, t_env *env)
{
	char	*slash_join;
	char	*cmd;
	int		i;
	int		j;

	j = -1;
	while (++j < data->cmd_size)
	{
		if (data->command[j] != NULL)
		{
			i = -1;
			while (split_path && split_path[++i])
			{
				slash_join = ft_strjoin(split_path[i], "/");
				cmd = ft_strjoin(slash_join, data->command[j]);
				if (!access(cmd, X_OK))
					execve(cmd, cmd_realoc(data), env_tochar(env->node));
				free(cmd);
				cmd = NULL;
				free(slash_join);
			}
			break ;
		}
	}
	error_cmdnotfound(data->command[j]);
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
