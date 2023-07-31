/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:41:39 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/31 13:31:26 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	double_pipe_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '|')
	{
		printf("Warning : start with `|'\n");
		return (false);
	}
	while (line[i])
	{
		if (line[i] == '|' && line[i - 1] == '|')
		{
			printf("Warning : consecutive pipe!\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	multi_redirection_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		{
			printf("Warning : more than three '<'\n");
			return (false);
		}
		if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			printf("Warning : more than three '>'\n");
			return (false);
		}
		if (line[i] == '<' && line[i + 1] == '>')
		{
			printf("'<>' is not implented!\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	blank_pipe_check(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			j = 1;
			while (line[i + j] == ' ' || line[i + j] == '\t')
				j++;
			if (line[i + j] == '|' && j > 1)
			{
				printf("Empty Command between '|'\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	blank_redirection_check(char *line)
{
	int	i;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			j = 2;
			while (line[i + j] == ' ' || line[i + j] == '\t')
				j++;
			if (line[i + j] == '<' || line[i + j] == '>')
			{
				printf("Only blank exist betwen redirections\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	readline_check(char *line)
{
	if (!double_pipe_check(line))
		return (false);
	if (!multi_redirection_check(line))
		return (false);
	if (!blank_pipe_check(line))
		return (false);
	if (!blank_redirection_check(line))
		return (false);
	printf("readline true\n");
	return (true);
}
