/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/31 14:32:46 by minjcho          ###   ########.fr       */
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

int	token_size(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == ' ' || str[i + j] == '\t')
			j++;
		i += j;
	}
}

void	split_splited_pipe(char *str)
{

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
