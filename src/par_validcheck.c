/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_validcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:41:39 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/28 16:35:55 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	double_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i - 1] == '|')
			return (false);
		i++;
	}
	return (true);
}

bool	readline_check(char *line)
{
	if (!double_pipe(line))
	{
		printf("consecutive pipe!\n");
		return (false);
	}
	return (true);
}