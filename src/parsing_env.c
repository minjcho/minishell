/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:05:13 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/24 21:33:33 by minjcho          ###   ########.fr       */
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

void	replace_variable(char **str, int idx, bool in_single_quote, t_env *env)
{
	char	*tmp;

	if ((*str)[idx] == '$' && is_alpha_num((*str)[idx + 1]) && !in_single_quote)
	{
		tmp = find_env_variable(&(*str)[idx + 1]);
		env_replace(str, tmp, env);
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
	while ((*str)[idx])
	{
		if (!is_in_quotes((*str)[idx], &in_single_quote, &in_double_quote))
		{
			if (handle_dollar_question(str, idx, in_single_quote))
				did_replace = true;
			else
				replace_variable(str, idx, in_single_quote, env);
		}
		idx++;
	}
	return (did_replace);
}
