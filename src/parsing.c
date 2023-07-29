/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/29 12:09:30 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_pipe(char *line)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '|')
			cnt++;
		i++;
	}
	if (line[i - 1] == '|')
		return (cnt - 1);
	return (cnt);
}

// void	parsing(t_mini *mini, char *line)
// {
// 	char **splited_pipe;

// 	if (!readline_check(line))
// 		return ;
// 	mini = malloc(sizeof(t_mini) * cnt_pipe(line) + 2);
// 	if (!mini)
// 		exit(1);
// 	splited_pipe = ft_split2(line, "|");
// 	int	i = 0;
// 	while (splited_pipe[i])
// 	{
// 		printf("i : %d\n", i);
// 		mini[i].command = ft_split2(splited_pipe[i], " ");
// 		int j = 0;
// 		while (mini[i].command[j])
// 		{
// 			printf("%s\n", mini[i].command[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	free(splited_pipe);
// }

void parsing(t_mini **mini, char *line)
{
	char **splited_pipe;
	if (!readline_check(line))
		return ;
	*mini = malloc(sizeof(t_mini) * cnt_pipe(line) + 1);
	if (!*mini)
		exit(1);
	splited_pipe = ft_split2(line, "|");
	int	i = 0;
	while (splited_pipe[i])
	{
		(*mini)[i].command = ft_split2(splited_pipe[i], " ");
		i++;
	}
	for(i = 0; splited_pipe[i]; i++) {
		free(splited_pipe[i]);
	}
	free(splited_pipe);
}
