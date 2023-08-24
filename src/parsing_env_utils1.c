/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:08:52 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/24 15:51:33 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_single_env(char **command, t_env *env)
{
	char	*env_value;

	if ((*command)[0] == '$' && (*command)[1] != '?' && (*command)[1])
	{
		env_value = ft_getenv((*command) + 1, env);
		if (env_value)
		{
			free(*command);
			*command = ft_strdup(env_value);
		}
		else
		{
			free(*command);
			*command = ft_strdup("");
		}
	}
}

int		where_is_next_quotation(char **str, int idx)
{
	int		jdx;

	jdx = idx + 1;
	while ((*str)[jdx])
	{
		if ((*str)[jdx] == (*str)[idx])
		{
			break ;
		}
		jdx++;
	}
	return (jdx);
}

// char	*remove_quotation_str(char *str)
// {
// 	int		idx;
// 	char	*tmp;
// 	bool	in_single_quote;
// 	bool	in_double_quote;

// 	idx = 0;
// 	in_single_quote = false;
// 	in_double_quote = false;
// 	while (str[idx])
// 	{
// 		if (str[idx] == '\"' && in_double_quote == false && \
// 			in_single_quote == false)
// 			in_double_quote = true;
// 		else if (str[idx] == '\"' && in_double_quote == true && \
// 				in_single_quote == false)
// 			in_double_quote = false;
// 		else if (str[idx] == '\'' && in_single_quote == false && \
// 			in_double_quote == false)
// 			in_single_quote = true;
// 		else if (str[idx] == '\'' && in_single_quote == true && \
// 				in_double_quote == false)
// 			in_single_quote = false;
// 		if (in_double_quote == true || in_single_quote == true)
// 		{
// 			idx = where_is_next_quotation(str, idx);
// 			continue ;
// 		}
// 		idx++;
// 	}
// }

void remove_quotation_str(char *str) {
    int read_pos = 0;
    int write_pos = 0;
    char current_quote = 0;

    while (str[read_pos]) {
        if ((str[read_pos] == '"' || str[read_pos] == '\'') && !current_quote) {
            // 따옴표 시작
            current_quote = str[read_pos];
        } else if (str[read_pos] == current_quote) {
            // 따옴표 종료
            current_quote = 0;
        } else {
            // 다른 문자를 결과에 쓰기
            str[write_pos++] = str[read_pos];
        }
        read_pos++;
    }
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

	idx = -1;
	while (mini[++idx].command)
	{
		jdx = -1;
		while (++jdx < mini[idx].cmd_size)
		{
			replace_env_in_double_quote(&mini[idx].command[jdx], env);
		}
	}
	remove_quotation_mini(mini);
}
