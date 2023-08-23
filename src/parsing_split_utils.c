/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:58:58 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/23 13:09:43 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_spaces(char *input, size_t len, size_t i)
{
	while (i < len && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

size_t	split_by_quote(char *input, size_t len, size_t i, char quote)
{
	i++;
	while (i < len && input[i] != quote)
		i++;
	if (i < len)
		i++;
	return (i);
}

size_t	split_by_special(char *input, size_t len, size_t i)
{
	while (i < len && is_special(input[i]))
		i++;
	return (i);
}

size_t	split_by_char(char *input, size_t len, size_t i)
{
	while (i < len && !is_special(input[i]) && \
			input[i] != ' ' && input[i] != '\'' && input[i] != '\"')
		i++;
	return (i);
}

void	split_segment(t_state *state, char *input, size_t len)
{
	if (state->quote)
	{
		state->i = split_by_quote(input, len, state->i, state->quote);
	}
	else if (is_special(input[state->i]))
	{
		state->i = split_by_special(input, len, state->i);
	}
	else
	{
		state->i = split_by_char(input, len, state->i);
	}
	state->result[state->idx] = \
					(char *)malloc(state->i - state->start + 1);
	ft_strncpy(state->result[state->idx], \
				input + state->start, state->i - state->start);
	state->result[state->idx][state->i - state->start] = '\0';
	state->idx++;
}
