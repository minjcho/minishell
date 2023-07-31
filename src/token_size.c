/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:04:56 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/31 15:29:44 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && quote_exist(&line[i]) && not_in_quote(&line[i]))
			
	}
}

int	token_size(char *line)
{
	int	token_size;

	token_size = 0;
	token_size += quote_count(line);
}
