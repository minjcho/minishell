/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:05:13 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/23 19:13:38 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_replace(char **str, char *tmp, t_env *env)
{
	char	*env_value;
	char	*new_str;
	char	*start_ptr;
	char	*var_with_dollar;

	var_with_dollar = (char *)malloc(ft_strlen(tmp) + 2);
	var_with_dollar[0] = '$';
	var_with_dollar[1] = '\0';
	ft_strcat(var_with_dollar, tmp);
	env_value = ft_getenv(tmp, env);
	if (!env_value)
		env_value = "";
	start_ptr = ft_strstr(*str, var_with_dollar);
	if (start_ptr)
	{
		new_str = (char *)malloc(ft_strlen(*str) - ft_strlen(var_with_dollar) \
								+ ft_strlen(env_value) + 1);
		ft_strncpy(new_str, *str, start_ptr - *str);
		ft_strcpy(new_str + (start_ptr - *str), env_value);
		ft_strcat(new_str, start_ptr + ft_strlen(var_with_dollar));
		free(*str);
		*str = new_str;
	}
	free(var_with_dollar);
}

char	*find_env_variable(char *str)
{
	int		jdx;
	char	*tmp;

	jdx = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[jdx] && str[jdx] != ' ' && str[jdx] != '\"' && \
			str[jdx] != '\t' && str[jdx] != '$')
	{
		tmp[jdx] = str[jdx];
		jdx++;
	}
	tmp[jdx] = '\0';
	return (tmp);
}

void	replace_env_in_double_quote(char **str, t_env *env)
{
	int		idx;
	char	*tmp;

	idx = 0;
	while ((*str)[idx])
	{
		if ((*str)[idx] == '$' && (*str)[idx + 1] != '?' && (*str)[idx + 1] \
			&& (*str)[idx + 1] != ' ' && (*str)[idx + 1] != '\"' && \
			(*str)[idx + 1] != '\t')
		{
			tmp = find_env_variable(&(*str)[idx + 1]);
			env_replace(str, tmp, env);
			free(tmp);
		}
		idx++;
	}
}

char	*process_double_quoted_str(char *str, t_env *env)
{
	int		len;
	char	*trimmed_str;

	len = ft_strlen(str);
	if (len > 2)
	{
		replace_env_in_double_quote(&str, env);
		trimmed_str = ft_strtrim(str, "\"");
		free(str);
		return (trimmed_str);
	}
	else if (len == 2)
	{
		free(str);
		return (ft_strdup(""));
	}
	return (str);
}

void	remove_double_quotation(t_mini *mini, t_env *env)
{
	int		idx;
	int		jdx;

	idx = 0;
	while (mini[idx].command)
	{
		jdx = 0;
		while (jdx < mini[idx].cmd_size)
		{
			if (mini[idx].command[jdx][0] == '\"' && \
				mini[idx].command[jdx][ft_strlen(mini[idx].command[jdx]) \
										- 1] == '\"')
			{
				mini[idx].command[jdx] = \
					process_double_quoted_str((mini[idx].command[jdx]), env);
			}
			jdx++;
		}
		idx++;
	}
}
