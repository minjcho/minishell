/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/31 15:11:13 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_cnt(char *line)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == '|')
			cnt++;
		line++;
	}
	return (cnt);
}

void	split_splited_pipe(char *line)
{
	char	**splited;

	splited = malloc(sizeof(char *) * token_size(line) + 1);
	if (!splited)
		exit(1);
	// tokenize(splited);
	tmp[token_size(line)] = 0;
	return (splited);
}

void	parsing(t_mini **mini, char *line)
{
	int		i;
	char	**splited_pipe;

	*mini = malloc(sizeof(t_mini) * pipe_cnt(line) + 1);
	if (!*mini)
		exit(1);
	splited_pipe = ft_split2(line, "|");
	i = 0;
	while (splited_pipe[i])
	{
		()
		(*mini)[i].token = split_splited_pipe(splited_pipe[i]);
		free(splited_pipe[i]);
		i++;
	}
	free(splited_pipe);
}
