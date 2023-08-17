/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:33:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/17 10:11:38 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_mini_struct(t_mini *mini)
{
	int	idx;

	idx = 0;
	while (mini[idx].command)
	{
		printf("Command #%d\n", idx + 1);
		printf("Cmd Size: %d\n", mini[idx].cmd_size);
		for (int j = 0; j < mini[idx].cmd_size; j++)
		{
			printf("  Element %d: %s\n", j + 1, mini[idx].command[j]);
		}
		printf("\n");
		idx++;
	}
}

void free_mini_struct(t_mini *mini, char **tmp_command)
{
	int idx = 0;
	while (mini[idx].command)
	{
		for (int j = 0; j < mini[idx].cmd_size; j++)
		{
			free(mini[idx].command[j]);
		}
		free(mini[idx].command);
		idx++;
	}
	free(mini);
	for (int i = 0; tmp_command[i]; i++)
	{
		free(tmp_command[i]);
	}
	free(tmp_command);
}


int main(int ac, char **av, char **env)
{
	t_mini	*mini;
	char	*line;
    char    **tmp_command;

	while (1)
	{
		line = readline("minishell$ ");
        tmp_command = parsing(&mini, line);
		print_mini_struct(mini);
		free_mini_struct(mini, tmp_command);
		add_history(line);
		free(line);
	}
}
