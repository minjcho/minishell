/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/24 16:27:07 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_rest_struct(t_mini **mini) //
{
	int	i;
	int	command_size;

	command_size = 0;
	while ((*mini)[command_size].command)
		command_size++;
	i = 0;
	while ((*mini)[i].command)
	{
		(*mini)[i].cnt = command_size;
		(*mini)[i].doc_cnt = 0;
		(*mini)[i].delete = 0;
		(*mini)[i].output_fd = 0;
		(*mini)[i].input_fd = 0;
		(*mini)[i].origin_in = dup(0);
		(*mini)[i].origin_out = dup(1);
		(*mini)[i].is_heredoc = 0;
		(*mini)[i].builtin_cnt = 0;
		(*mini)[i].is_signal = 0;
		i++;
	}
}

bool	check_command_pipe(char **str) //
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		idx++;
	}
	idx--;
	if (str[idx][0] == '|')
	{
		ft_putstr_fd("Error: syntax error near unexpected token `|'\n", 2);
		return (false);
	}
	return (true);
}

bool	parsing(t_mini **mini, char *line) //
{
	char	**tmp_command;
	bool	is_ok;

	is_ok = true;
	tmp_command = split_string(line);
	put_struct(mini, tmp_command);
	fill_rest_struct(mini);
	is_ok = check_command_pipe(tmp_command);
	command_free(tmp_command);
	return (is_ok);
}

bool	check_pipe(t_mini *mini) //
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
			if (mini[idx].command[jdx][0] == '|' \
				&& ft_strlen(mini[idx].command[jdx]) > 1)
			{
				ft_putstr_fd("Error: syntax error near \
								unexpected token `|'\n", 2);
				ft_putstr_fd("Error: syntax error near \
								unexpected token `|'\n", 2);
				return (true);
			}
			jdx++;
		}
		idx++;
	}
	return (false);
}

int	skip_quotes(char *command, int idx) //
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

bool	is_open(t_mini *mini) //
{
	int	idx;
	int	jdx;
	int	kdx;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			kdx = 0;
			while (mini[idx].command[jdx][kdx])
			{
				if (mini[idx].command[jdx][kdx] == '\'' || mini[idx].command[jdx][kdx] == '\"')
				{
					kdx = skip_quotes(mini[idx].command[jdx], kdx);
					if (kdx == -2)
						return (true);
				}
				else
					kdx++;
			}
			jdx++;
		}
		idx++;
	}
	return (false);
}

bool	check_struct(t_mini	*mini, t_env *env) //
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
