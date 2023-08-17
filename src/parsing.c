/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/17 10:11:58 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char is_special(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

char **split_string(const char *input)
{
	size_t len = strlen(input);
	char **result = (char **)malloc((len + 1) * sizeof(char *));
	int idx = 0;
	size_t i = 0;

	while (i < len)
	{
		while (i < len && (input[i] == ' ' || input[i] == '\t')) i++;
		if (i == len)
			break;
		size_t start = i;
		if (input[i] == '\'' || input[i] == '\"') {
			char quote = input[i++];
			while (i < len && input[i] != quote) i++;
			if (i < len) i++;
		} else if (is_special(input[i])) {
			while (i < len && input[i] == input[start]) i++;
		} else {
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
			if (tmp_command[i+1] == NULL) cmd_count++;

			(*mini)[cmd_idx].command = (char **)malloc((cmd_count + 1) * sizeof(char *));
			for (int k = 0; k < cmd_count; k++) {
				(*mini)[cmd_idx].command[k] = strdup(tmp_command[start_idx + k]);
			}
			(*mini)[cmd_idx].command[cmd_count] = NULL;

			(*mini)[cmd_idx].cmd_size = cmd_count;

			cmd_count = 0;
			cmd_idx++;
			start_idx = i + 1;
		} else {
			cmd_count++;
		}
	}

	(*mini)[cmd_idx].command = NULL;
	(*mini)[cmd_idx].cmd_size = 0;
}


char **parsing(t_mini **mini, char *line)
{
	int		i;
	char	**tmp_command;

	i = 0;
	tmp_command = split_string(line);
	put_struct(mini, tmp_command);
	return (tmp_command);
}
