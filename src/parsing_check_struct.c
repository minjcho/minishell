/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:29:00 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 13:29:16 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_pipe(t_mini *mini)
{
	int	idx;
	int	jdx;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			if (mini[idx].command[jdx][0] == '|' \
				&& ft_strlen(mini[idx].command[jdx]) > 1)
			{
				ft_putstr_fd(\
					"Error: syntax error near unexpected token `|'\n", 2);
				return (true);
			}
			jdx++;
		}
		idx++;
	}
	return (false);
}

int	skip_quotes(char *command, int idx)
{
	char	quote;

	quote = command[idx];
	idx++;
	while (command[idx] && command[idx] != quote)
		idx++;
	if (command[idx] == quote)
		return (idx + 1);
	else
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (-2);
	}
}

bool	is_open_in_command(char **command, int cmd_size)
{
	int	jdx;
	int	kdx;

	jdx = -1;
	while (++jdx < cmd_size)
	{
		kdx = 0;
		while (command[jdx][kdx])
		{
			if (command[jdx][kdx] == '\'' || command[jdx][kdx] == '\"')
			{
				kdx = skip_quotes(command[jdx], kdx);
				if (kdx == -2)
					return (true);
			}
			else
				kdx++;
		}
	}
	return (false);
}

bool	is_open(t_mini *mini)
{
	int	idx;

	idx = -1;
	while (mini[++idx].command)
	{
		if (is_open_in_command(mini[idx].command, mini[idx].cmd_size))
			return (true);
	}
	return (false);
}

bool	check_struct(t_mini	*mini, t_env *env)
{
	int	idx;
	int	struct_size;

	idx = 0;
	struct_size = 0;
	while (mini[struct_size].command)
		struct_size++;
	while (mini[idx].command)
	{
		if (mini[idx].cmd_size == 0 && idx != struct_size)
		{
			ft_putstr_fd("Error: syntax error near unexpected token `|'\n", 2);
			return (true);
		}
		idx++;
	}
	if (is_open(mini))
		return (true);
	if (check_redirection(mini))
		return (true);
	if (check_pipe(mini))
		return (true);
	replace_env(mini, env);
	return (false);
}
