/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:06:50 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/21 15:00:13 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
		strncpy(new_str, *str, start_ptr - *str); // 변수 앞 부분 복사
		strcpy(new_str + (start_ptr - *str), env_value); // 환경 변수 값 복사
		strcat(new_str, start_ptr + ft_strlen(var_with_dollar)); // 변수 뒷 부분 복사
*/

void	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (src[i])
			dest[i] = src[i];
		else
			dest[i] = '\0';
		i++;
	}
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}	
	dest[i] = '\0';
}

void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}	
	dest[dest_len + i] = '\0';
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (!*to_find)
		return (str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j] && str[i + j] && str[i + j] == to_find[j])
			j++;
		if (!to_find[j])
			return (str + i);
		i++;
	}
	return (0);
}

char	is_special(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

char	**split_string(char *input)
{
	size_t	len = ft_strlen(input);
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
		ft_strncpy(result[idx], input + start, i - start);
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
        if (ft_strcmp(tmp_command[i], "|") == 0) total_commands++;
    }
    total_commands++;
    *mini = (t_mini *)malloc((total_commands + 1) * sizeof(t_mini));

    int cmd_idx = 0;
    int cmd_count = 0;
    int start_idx = 0;

    for (int i = 0; tmp_command[i]; i++)
    {
        if (ft_strcmp(tmp_command[i], "|") == 0 || tmp_command[i+1] == NULL) {
            if (tmp_command[i+1] == NULL && ft_strcmp(tmp_command[i], "|") == 0) {
                (*mini)[cmd_idx].command = (char **)malloc((cmd_count + 1) * sizeof(char *));
                for (int k = 0; k < cmd_count; k++) {
                    (*mini)[cmd_idx].command[k] = ft_strdup(tmp_command[start_idx + k]);
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
                    (*mini)[cmd_idx].command[k] = ft_strdup(tmp_command[start_idx + k]);
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

bool	consecutive_redirection(t_mini *mini)
{
	int	idx;
	int	jdx;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			if (mini[idx].command[jdx][0] == '<' && mini[idx].command[jdx + 1] && (mini[idx].command[jdx + 1][0] == '<' || mini[idx].command[jdx + 1][0] == '>'))
			{
				printf("Error: consecutive '<'\n");
				return (true);
			}
			if (mini[idx].command[jdx][0] == '>' && mini[idx].command[jdx + 1] && (mini[idx].command[jdx + 1][0] == '>' || mini[idx].command[jdx + 1][0] == '<'))
			{
				printf("Error: consecutive '>'\n");
				return (true);
			}
			jdx++;
		}
		idx++;
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
				printf("Error: empty '<'\n");
				return (true);
			}
			if (mini[idx].command[jdx][0] == '>' && !mini[idx].command[jdx + 1])
			{
				printf("Error: empty '>'\n");
				return (true);
			}
			jdx++;
		}
		idx++;
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
			if (mini[idx].command[jdx][0] == '<' && ft_strlen(mini[idx].command[jdx]) > 2)
			{
				printf("Error: more than three '<'\n");
				return (true);
			}
			if (mini[idx].command[jdx][0] == '>' && ft_strlen(mini[idx].command[jdx]) > 2)
			{
				printf("Error: more than three '>'\n");
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
			if (mini[idx].command[jdx][0] == '|' && ft_strlen(mini[idx].command[jdx]) > 1)
			{
				printf("Error: more than one '|'\n");
				return (true);
			}
			jdx++;
		}
		idx++;
	}
	return (false);
}

void	env_replace(char **str, char *tmp, t_env *env)
{
	char	*env_value;
	char	*new_str;
	char	*start_ptr;
	char	*var_with_dollar;

	// $와 변수 이름을 연결해서 var_with_dollar에 저장
	var_with_dollar = (char *)malloc(ft_strlen(tmp) + 2); 
	var_with_dollar[0] = '$';
	var_with_dollar[1] = '\0';
	ft_strcat(var_with_dollar, tmp);

	// 환경 변수 값을 가져옴
	env_value = ft_getenv(tmp, env);
	if (!env_value)
		env_value = "";  // 환경 변수 값이 없을 경우 빈 문자열로 처리

	// 원본 문자열에서 변수 부분을 찾음
	start_ptr = ft_strstr(*str, var_with_dollar);
	if (start_ptr)
	{
		// 새 문자열 생성 및 복사
		new_str = (char *)malloc(ft_strlen(*str) - ft_strlen(var_with_dollar) + ft_strlen(env_value) + 1);
		ft_strncpy(new_str, *str, start_ptr - *str); // 변수 앞 부분 복사
		ft_strcpy(new_str + (start_ptr - *str), env_value); // 환경 변수 값 복사
		ft_strcat(new_str, start_ptr + ft_strlen(var_with_dollar)); // 변수 뒷 부분 복사
		
		// 원본 문자열 메모리 해제 및 새로운 문자열로 업데이트
		free(*str);
		*str = new_str;
	}
	free(var_with_dollar);
}

void replace_env_in_double_quote(char **str, t_env *env)
{
    int idx;
    int jdx;
    int len;
    char *tmp;

    idx = 0;
    len = ft_strlen(*str);
    tmp = (char *)malloc(sizeof(char) * (len + 1));
    while ((*str)[idx])
    {
        if ((*str)[idx] == '$' && (*str)[idx + 1] != '?' && (*str)[idx + 1] && (*str)[idx + 1] != ' ' && (*str)[idx + 1] != '\"' && (*str)[idx + 1] != '\t')
        {
            jdx = 0;
            while ((*str)[idx + jdx + 1] && (*str)[idx + jdx + 1] != ' ' && (*str)[idx + jdx + 1] != '\"' && (*str)[idx + jdx + 1] != '\t' && (*str)[idx + jdx + 1] != '$')
            {
                tmp[jdx] = (*str)[idx + jdx + 1];
                jdx++;
            }
            tmp[jdx] = '\0';
            env_replace(str, tmp, env);
        }
        idx++;
    }

    free(tmp);
}

void	remove_double_quotation(t_mini *mini, t_env *env)
{
	int	idx;
	int	jdx;
	int	len;
	char	*trimmed_str;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			len = ft_strlen(mini[idx].command[jdx]);
			if (mini[idx].command[jdx][0] == '\"' && mini[idx].command[jdx][len - 1] == '\"' && len > 2)
			{
				replace_env_in_double_quote(&(mini[idx].command[jdx]), env);
				trimmed_str = ft_strtrim(mini[idx].command[jdx], "\"");
				free(mini[idx].command[jdx]);
				mini[idx].command[jdx] = trimmed_str;
				// mini[idx].command[jdx] = ft_strtrim(mini[idx].command[jdx], "\"");
			}
			else if (mini[idx].command[jdx][0] == '\"' && mini[idx].command[jdx][len - 1] == '\"' && len == 2)
			{
				free(mini[idx].command[jdx]);
				mini[idx].command[jdx] = ft_strdup("");
			}
			jdx++;
		}
		idx++;
	}
}

void	put_global_siganl(char **str)
{
	char	*tmp;
	char	*new_str;
	char	*start_ptr;

	tmp = ft_itoa(global_signal);
	start_ptr = ft_strstr(*str, "$?");
	if (start_ptr)
	{
		new_str = (char *)malloc(ft_strlen(*str) - ft_strlen("$?") + ft_strlen(tmp) + 1);
		ft_strncpy(new_str, *str, start_ptr - *str);
		ft_strcpy(new_str + (start_ptr - *str), tmp);
		ft_strcat(new_str, start_ptr + ft_strlen("$?"));
		free(*str);
		*str = new_str;
	}
	free(tmp);
}

bool	replace_dollar_question(t_mini **mini)
{
	int	i;
	int	j;
	int	k;
	bool	did_replace;

	i = 0;
	while ((*mini)[i].command)
	{
		j = 0;
		while ((*mini)[i].command[j])
		{
			k = 0;
			while ((*mini)[i].command[j][k])
			{
				if ((*mini)[i].command[j][k] == '$' && (*mini)[i].command[j][k + 1] && (*mini)[i].command[j][k + 1] == '?' && (*mini)[i].command[j][0] != '\'')
				{
					did_replace = true;
					put_global_siganl(&(*mini)[i].command[j]);
				}
				k++;
			}
			j++;
		}
		i++;
	}
	return (did_replace);
}

void	remove_single_quotation(t_mini *mini)
{
	int	idx;
	int	jdx;
	int	len;
	char	*trimmed_str;
	bool	did_replace;

	did_replace = replace_dollar_question(&mini);
	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			len = ft_strlen(mini[idx].command[jdx]);
			if (mini[idx].command[jdx][0] == '\'' && mini[idx].command[jdx][len - 1] == '\'' && len > 2)
			{
				trimmed_str = ft_strtrim(mini[idx].command[jdx], "\'");
				free(mini[idx].command[jdx]);
				mini[idx].command[jdx] = trimmed_str;
				// mini[idx].command[jdx] = ft_strtrim(mini[idx].command[jdx], "\'");
			}
			else if (mini[idx].command[jdx][0] == '\'' && mini[idx].command[jdx][len - 1] == '\'' && len == 2)
			{
				free(mini[idx].command[jdx]);
				mini[idx].command[jdx] = ft_strdup("");
			}
			jdx++;
		}
		idx++;
	}
	if (did_replace)
		global_signal = 0;
}

void	replace_env(t_mini *mini, t_env *env)
{
	int	idx;
	int	jdx;
	char	*env_value;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			if (mini[idx].command[jdx][0] == '$' && mini[idx].command[jdx][1] != '?' && mini[idx].command[jdx][1])
			{
				env_value = ft_getenv(mini[idx].command[jdx] + 1, env);
				if (env_value)
				{
					free(mini[idx].command[jdx]);
					mini[idx].command[jdx] = ft_strdup(env_value);
				}
				else
				{
					free(mini[idx].command[jdx]);
					mini[idx].command[jdx] = ft_strdup("");
				}
				// mini[idx].command[jdx] = ft_getenv(mini[idx].command[jdx] + 1, env);
				// printf("mini[idx].command[jdx]: %s\n", mini[idx].command[jdx]);
			}
			jdx++;
		}
		idx++;
	}
	remove_double_quotation(mini, env);
	remove_single_quotation(mini);
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
		if (mini[idx].cmd_size == 0 && idx != struct_size - 1)
		{
			printf("Error: Empty command\n");
			return (true);
		}
		idx++;
	}
	if (check_redirection(mini))
		return (true);
	if (check_pipe(mini))
		return (true);
	replace_env(mini, env);
	return (false);
}
