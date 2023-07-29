/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:33:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/29 12:02:53 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_mini(t_mini *mini, int cnt)
{
	for (int i = 0; i < cnt + 1; i++)
	{
		printf("i : %d\n", i);
		for(int j = 0; mini[i].command[j]; j++) {
			printf("%s\n", mini[i].command[j]);
		}
	}
}

int main(int ac, char **av, char **env)
{
	t_mini	*mini;
	char	*line;
	while (1)
	{
		line = readline("minishell$ ");
		parsing(&mini, line);
		add_history(line);
		// print_mini(mini, cnt_pipe(line));
		for(int i = 0; i < cnt_pipe(line) + 1; i++) {
			for(int j = 0; mini[i].command[j]; j++) {
				free(mini[i].command[j]);
			}
			free(mini[i].command);
		}
		free(mini);
		free(line);
	}
}