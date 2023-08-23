/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:00:37 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/23 13:02:01 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char **tmp_command)
{
	int	i;
	int	total_commands;

	i = -1;
	total_commands = 0;
	while (tmp_command[++i])
	{
		if (ft_strcmp(tmp_command[i], "|") == 0)
			total_commands++;
	}
	return (total_commands + 1);
}

void	allocate_and_set_command(t_mini *mini, char **tmp_command, \
									int cmd_count, int start_idx)
{
	int	k;

	mini->command = (char **)malloc((cmd_count + 1) * sizeof(char *));
	k = -1;
	while (++k < cmd_count)
	{
		mini->command[k] = ft_strdup(tmp_command[start_idx + k]);
	}
	mini->command[cmd_count] = NULL;
	mini->cmd_size = cmd_count;
}

int	get_command_count(char **tmp_command)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tmp_command[i])
	{
		if (ft_strcmp(tmp_command[i], "|") == 0 || \
			tmp_command[i + 1] == NULL)
		{
			if (tmp_command[i + 1] == NULL && \
				ft_strcmp(tmp_command[i], "|") != 0)
				count++;
			else
				count = 0;
		}
		else
			count++;
		i++;
	}
	return (count);
}

void	update_indices_and_count(int *cmd_count, int *cmd_idx, \
									int *start_idx, int i)
{
	*cmd_count = 0;
	(*cmd_idx)++;
	*start_idx = i + 1;
}

void	put_struct(t_mini **mini, char **tmp_command)
{
	int	total_commands;
	int	cmd_idx;
	int	cmd_count;
	int	start_idx;
	int	i;

	total_commands = count_pipes(tmp_command);
	*mini = (t_mini *)malloc((total_commands + 1) * sizeof(t_mini));
	cmd_idx = 0;
	cmd_count = 0;
	start_idx = 0;
	i = -1;
	while (tmp_command[++i])
	{
		if (ft_strcmp(tmp_command[i], "|") == 0 || tmp_command[i + 1] == NULL)
		{
			cmd_count = get_command_count(tmp_command);
			allocate_and_set_command(&(*mini)[cmd_idx], tmp_command, \
									cmd_count, start_idx);
			update_indices_and_count(&cmd_count, &cmd_idx, &start_idx, i);
		}
	}
	(*mini)[cmd_idx].command = NULL;
	(*mini)[cmd_idx].cmd_size = 0;
}
