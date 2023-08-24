/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:02:55 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/24 20:37:30 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_and_print_error(char *current, char *next)
{
	if (current[0] == '<' && next && (next[0] == '<' || next[0] == '>'))
	{
		ft_putstr_fd("Error: parse error near `<'\n", 2);
		return (true);
	}
	if (current[0] == '>' && next && (next[0] == '>' || next[0] == '<'))
	{
		ft_putstr_fd("Error: parse error near `>'\n", 2);
		return (true);
	}
	return (false);
}

bool	consecutive_redirection(t_mini *mini)
{
	int	idx;
	int	jdx;

	idx = -1;
	while (mini[++idx].command)
	{
		jdx = -1;
		while (++jdx < mini[idx].cmd_size)
		{
			if (check_and_print_error(mini[idx].command[jdx], \
				mini[idx].command[jdx + 1]))
			{
				return (true);
			}
		}
	}
	return (false);
}

bool	check_empty_redirection(t_mini *mini)
{
	int	idx;
	int	jdx;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			if (mini[idx].command[jdx][0] == '<' && !mini[idx].command[jdx + 1])
			{
				ft_putstr_fd("Error: empty '<'\n", 2);
				return (true);
			}
			if (mini[idx].command[jdx][0] == '>' && !mini[idx].command[jdx + 1])
			{
				ft_putstr_fd("Error: empty '>'\n", 2);
				return (true);
			}
			jdx++;
		}
		idx++;
	}
	return (false);
}

bool	has_invalid_redirection(char *token)
{
	if (token[0] == '<' && ft_strlen(token) > 2)
	{
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (true);
	}
	if (token[0] == '>' && ft_strlen(token) > 2)
	{
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (true);
	}
	return (false);
}

bool	check_redirection(t_mini *mini)
{
	int	idx;
	int	jdx;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			if (has_invalid_redirection(mini[idx].command[jdx]))
			{
				return (true);
			}
			jdx++;
		}
		idx++;
	}
	if (consecutive_redirection(mini))
		return (true);
	if (check_empty_redirection(mini))
		return (true);
	return (false);
}
