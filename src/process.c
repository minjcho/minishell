/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:41:21 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:47:43 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_mini *data, t_env *env)
{
	int	i;

	i = -1;
	//heredoc_ready(data, env);
	while (++i < data->cnt)
	{
		redirection_ready(&data[i]);
	}
	builtin_counter(data);
	if (data->builtin_cnt == 1 && data->cnt == 1)
	{
		if (data->input_fd)
		{
			dup2(data->input_fd, 0);
			close(data->input_fd);
		}
		if (data->output_fd)
		{
			dup2(data->output_fd, 1);
			close(data->output_fd);
		}
		do_builtin(data, env);
		dup2(data->origin_in, 0);
		dup2(data->origin_out, 1);
		return ;
	}
	process_start2(data, env);
}

void	first_excute(t_mini *data, t_env *env)
{
	int		i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i] != NULL)
		{
			//if (access(data->command[i], X_OK) == 0) // error issue
			execve(data->command[i], cmd_realoc(data), env_tochar(env->node));
			// if (execve(data->command[i], data->command, NULL) == -1)
			// 	break;
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
				//if (access(cmd, X_OK) == 0)
				execve(cmd, cmd_realoc(data), NULL);
				free(cmd);
			}
		}
		free(slash_join);
	}
	error_cmdnotfound(data->command[0], data);
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