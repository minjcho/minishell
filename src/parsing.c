/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/28 15:15:21 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split2(char *str, int c)
{
	char **result;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	result = (char **)malloc(sizeof(char *) * 100);
	while (str[i])
	{
		k = 0;
		result[j] = (char *)malloc(sizeof(char) * 100);
		while (str[i] && str[i] != c)
			result[j][k++] = str[i++];
		result[j][k] = '\0';
		j++;
		if (str[i])
			i++;
	}
	result[j] = NULL;
	return (result);
}

void free_split2(char **split)
{
	int i;

	if (split != NULL)
	{
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void parsing(t_mini mini[100], char *line)
{
	char **splited_pipe;

	splited_pipe = ft_split2(line, '|');
	int i = 0;
	while (splited_pipe[i])
	{
		mini[i].command = ft_split2(splited_pipe[i], ' ');
		printf("mini[%d].command[0] %s\n", i, mini[i].command[0]);
		i++;
	}
	// free_split2(splited_pipe);
	// for(int j=0; j<i; j++)
	// {
	// 	free_split2(mini[j].command);
	// }
}
