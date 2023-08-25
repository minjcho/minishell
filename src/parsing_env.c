/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:05:13 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 15:47:04 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha_num(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

bool	is_in_quotes(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == '\"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (true);
	}
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (true);
	}
	return (false);
}

bool	handle_dollar_question(char **str, int idx, bool in_single_quote)
{
	if ((*str)[idx] == '$' && (*str)[idx + 1] == '?' && !in_single_quote)
	{
		put_g_signal(&(*str), idx);
		return (true);
	}
	return (false);
}

void	replace_variable(char **str, int idx, t_env *env, bool in_double_quote)
{
	char	*tmp;

	if ((*str)[idx] == '$' && is_alpha_num((*str)[idx + 1]))
	{
		tmp = find_env_variable(&(*str)[idx + 1]);
		env_replace(str, tmp, env, in_double_quote);
		free(tmp);
	}
}

bool	replace_env_in_double_quote(char **str, t_env *env)
{
	int		idx;
	bool	in_single_quote;
	bool	in_double_quote;
	bool	did_replace;

	idx = 0;
	in_single_quote = false;
	in_double_quote = false;
	did_replace = false;
	while ((*str) && (*str)[idx])
	{
		if (!is_in_quotes((*str)[idx], &in_single_quote, &in_double_quote))
		{
			if (handle_dollar_question(str, idx, in_single_quote))
				did_replace = true;
			else if (!in_single_quote && (*str)[idx] == '$' && \
					is_alpha_num((*str)[idx + 1]))
				replace_variable(str, idx, env, in_double_quote);
		}
		idx++;
	}
	return (did_replace);
}
