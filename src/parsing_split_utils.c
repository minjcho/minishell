/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:58:58 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 13:32:42 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_spaces(char *input, size_t len, size_t i)
{
	while (i < len && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

size_t	split_by_special(char *input, size_t len, size_t i, char quote)
{
	while (i < len && (!quote && is_special_t(input[i])))
		i++;
	return (i);
}

size_t	split_by_char(char *input, size_t len, size_t i, char *quote)
{
	while (i < len)
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!*quote)
			{
				*quote = input[i];
				i++;
				continue ;
			}
			else if (*quote == input[i])
			{
				*quote = 0;
				i++;
				continue ;
			}
		}
		if (!*quote && (is_special_t(input[i]) || input[i] == ' '))
			break ;
		i++;
	}
	return (i);
}

void	split_segment(t_state *state, char *input, size_t len)
{
	char	quote;

	quote = 0;
	if (is_special_t(input[state->i]))
	{
		state->i = split_by_special(input, len, state->i, quote);
	}
	else
	{
		state->i = split_by_char(input, len, state->i, &quote);
	}
	state->result[state->idx] = (char *)malloc(state->i - state->start + 1);
	if (!state->result[state->idx])
		error_malloc();
	ft_strncpy(state->result[state->idx], \
				input + state->start, state->i - state->start);
	state->result[state->idx][state->i - state->start] = '\0';
	state->idx++;
}

char	**split_string(char *input)
{
	const size_t	len = ft_strlen(input);
	t_state			state;

	state.result = (char **)malloc((len + 1) * sizeof(char *));
	if (!state.result)
		error_malloc();
	state.idx = 0;
	state.i = 0;
	while (state.i < len)
	{
		state.i = skip_spaces(input, len, state.i);
		if (state.i == len)
			break ;
		state.start = state.i;
		split_segment(&state, input, len);
	}
	state.result[state.idx] = NULL;
	return (state.result);
}
