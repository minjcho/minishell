/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:33:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/31 13:28:06 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_mini(t_mini *mini)
// {
// 	for (int i = 0; i < mini.cnt; i++)
// 	{
// 		printf("i : %d\n", i);
// 		for(int j = 0; mini[i].command[j]; j++) {
// 			printf("%s\n", mini[i].command[j]);
// 		}
// 	}
// }

int main(int ac, char **av, char **env)
{
	t_mini	*mini;
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (readline_check(line))
		{
			printf("what u typed : %s\n", line);
			parsing(&mini, line);
			// print_mini(mini);
			// free_parsing(&mini);
		}
		add_history(line);
		free(line);
	}
}