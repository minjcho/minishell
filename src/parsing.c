/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/17 15:43:50 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_special(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

char	**split_string(const char *input)
{
	size_t	len = strlen(input);
	char	**result = (char **)malloc((len + 1) * sizeof(char *));
	int		idx = 0;
	size_t	i = 0;

	while (i < len)
	{
		while (i < len && (input[i] == ' ' || input[i] == '\t')) i++;
		if (i == len)
			break;
		size_t start = i;
		if (input[i] == '\'' || input[i] == '\"')
		{
			char quote = input[i++];
			while (i < len && input[i] != quote) i++;
			if (i < len) i++;
		}
		else if (is_special(input[i]))
		{
			while (i < len && input[i] == input[start]) i++;
		}
		else
		{
			while (i < len && !is_special(input[i]) && input[i] != ' ' && input[i] != '\'' && input[i] != '\"')
			i++;
		}
		result[idx] = (char *)malloc(i - start + 1);
		strncpy(result[idx], input + start, i - start);
		result[idx][i - start] = '\0';
		idx++;
	}
	result[idx] = NULL;
	return (result);
}

void put_struct(t_mini **mini, char **tmp_command)
{
    int total_commands = 0;
    for (int i = 0; tmp_command[i]; i++) {
        if (strcmp(tmp_command[i], "|") == 0) total_commands++;
    }
    total_commands++;
    *mini = (t_mini *)malloc((total_commands + 1) * sizeof(t_mini));

    int cmd_idx = 0;
    int cmd_count = 0;
    int start_idx = 0;

    for (int i = 0; tmp_command[i]; i++)
    {
        if (strcmp(tmp_command[i], "|") == 0 || tmp_command[i+1] == NULL) {
            if (tmp_command[i+1] == NULL && strcmp(tmp_command[i], "|") == 0) {
                (*mini)[cmd_idx].command = (char **)malloc((cmd_count + 1) * sizeof(char *));
                for (int k = 0; k < cmd_count; k++) {
                    (*mini)[cmd_idx].command[k] = strdup(tmp_command[start_idx + k]);
                }
                (*mini)[cmd_idx].command[cmd_count] = NULL;
                (*mini)[cmd_idx].cmd_size = cmd_count;
                cmd_idx++;
                cmd_count = 0;
                (*mini)[cmd_idx].command = (char **)malloc(1 * sizeof(char *));
                (*mini)[cmd_idx].command[0] = NULL;
                (*mini)[cmd_idx].cmd_size = 0;
            } else {
                if (tmp_command[i+1] == NULL) cmd_count++;
                (*mini)[cmd_idx].command = (char **)malloc((cmd_count + 1) * sizeof(char *));
                for (int k = 0; k < cmd_count; k++) {
                    (*mini)[cmd_idx].command[k] = strdup(tmp_command[start_idx + k]);
                }
                (*mini)[cmd_idx].command[cmd_count] = NULL;
                (*mini)[cmd_idx].cmd_size = cmd_count;
                cmd_count = 0;
            }
            cmd_idx++;
            start_idx = i + 1;
        } else {
            cmd_count++;
        }
    }

    (*mini)[cmd_idx].command = NULL;
    (*mini)[cmd_idx].cmd_size = 0;
}

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
		i++;
	}
}

char	**parsing(t_mini **mini, char *line)
{
	int		i;
	char	**tmp_command;

	i = 0;
	tmp_command = split_string(line);
	put_struct(mini, tmp_command);
	fill_rest_struct(mini);
	return (tmp_command);
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
			if (mini[idx].command[jdx][0] == '<' && strlen(mini[idx].command[jdx]) > 2)
			{
				printf("Error: more than three '<'\n");
				return (true);
			}
			if (mini[idx].command[jdx][0] == '>' && strlen(mini[idx].command[jdx]) > 2)
			{
				printf("Error: more than three '>'\n");
				return (true);
			}
			jdx++;
		}
		idx++;
	}
	return (false);	
}

bool	check_struct(t_mini	*mini)
{
	int	idx;
	int	struct_size;

	idx = 0;
	struct_size = 0;
	while (mini[struct_size].command)
		struct_size++;
	while (mini[idx].command)
	{
		if (mini[idx].cmd_size == 0 && idx != struct_size - 1)
		{
			printf("Error: Empty command\n");
			return (true);
		}
		idx++;
	}
	if (check_redirection(mini))
		return (true);
	return (false);
}
