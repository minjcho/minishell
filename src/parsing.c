/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 13:39:39 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_rest_struct(t_mini **mini)
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
		(*mini)[i].echo_fail = 0;
		i++;
	}
}

bool	check_command_pipe(char **str)
{
	int	idx;

	if (!(*str))
		return (false);
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

bool	parsing(t_mini **mini, char *line)
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
