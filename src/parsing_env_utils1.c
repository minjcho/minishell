/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:08:52 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 15:35:02 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotation_str(char *str)
{
	int		read_pos;
	int		write_pos;
	char	current_quote;

	read_pos = 0;
	write_pos = 0;
	current_quote = 0;
	while (str && str[read_pos])
	{
		if ((str[read_pos] == '\"' || str[read_pos] == '\'') && !current_quote)
		{
			current_quote = str[read_pos];
		}
		else if (str[read_pos] == current_quote)
			current_quote = 0;
		else
			str[write_pos++] = str[read_pos];
		read_pos++;
	}
	if (str)
		str[write_pos] = '\0';
}

void	remove_quotation_mini(t_mini *mini)
{
	int		idx;
	int		jdx;

	idx = -1;
	while (mini[++idx].command)
	{
		jdx = -1;
		while (++jdx < mini[idx].cmd_size)
		{
			remove_quotation_str(mini[idx].command[jdx]);
		}
	}
}

void	replace_env(t_mini *mini, t_env *env)
{
	int		idx;
	int		jdx;
	bool	did_replace;

	idx = -1;
	did_replace = false;
	while (mini[++idx].command)
	{
		jdx = -1;
		while (++jdx < mini[idx].cmd_size)
		{
			did_replace = \
					replace_env_in_double_quote(&mini[idx].command[jdx], env);
		}
	}
	remove_quotation_mini(mini);
	if (did_replace == true)
		g_signal = 0;
}
