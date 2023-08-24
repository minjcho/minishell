/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:05:13 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/24 16:48:24 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_replace(char **str, char *tmp, t_env *env) //
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

int	is_alpha_num(char c) //
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*find_env_variable(char *str) //
{
	int		jdx;
	char	*tmp;

	jdx = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[jdx] && is_alpha_num(str[jdx]))
	{
		tmp[jdx] = str[jdx];
		jdx++;
	}
	tmp[jdx] = '\0';
	return (tmp);
}

bool	replace_env_in_double_quote(char **str, t_env *env) //
{
	int		idx;
	char	*tmp;
	bool	in_single_quote;
	bool	in_double_quote;
	char	*start_ptr;
	bool	did_replace;

	idx = 0;
	in_single_quote = false;
	in_double_quote = false;
	while ((*str)[idx])
	{
		if ((*str)[idx] == '\"' && in_double_quote == false && \
			in_single_quote == false)
			in_double_quote = true;
		else if ((*str)[idx] == '\"' && in_double_quote == true && \
				in_single_quote == false)
			in_double_quote = false;
		else if ((*str)[idx] == '\'' && in_single_quote == false && \
			in_double_quote == false)
			in_single_quote = true;
		else if ((*str)[idx] == '\'' && in_single_quote == true && \
				in_double_quote == false)
			in_single_quote = false;
		else if ((*str)[idx] == '$' && (*str)[idx + 1] && (*str)[idx + 1] == '?' && in_single_quote == false)
		{
			put_g_signal(&(*str), idx);
			did_replace = true;
		}
		else if ((*str)[idx] == '$' && is_alpha_num((*str)[idx + 1]) \
				&& in_single_quote == false)
		{
			tmp = find_env_variable(&(*str)[idx + 1]);
			env_replace(str, tmp, env);
			free(tmp);
		}
		idx++;
	}
	return (did_replace);
}
