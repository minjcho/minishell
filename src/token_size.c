/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:04:56 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/31 15:51:38 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_exist(char *line, int idx)
{
	int		i;
	int		cnt;
	bool	status;

	i = 0;
	cnt = 0;
	while (i < idx)
	{
		if (line[i] == line[idx])
			cnt++;
		i++;
	}
	if (cnt % 2 == 1)
		return (true);
}

int	quote_count(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && quote_exist(line, i) && between_quote(line, i))
			
	}
}

int	token_size(char *line)
{
	int	token_size;

	token_size = 0;
	token_size += quote_count(line);
}
