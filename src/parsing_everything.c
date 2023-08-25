/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_everything.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:31:05 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/25 13:30:59 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_special_t(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ',' || c == '\t');
}

void	env_replace(char **str, char *tmp, t_env *env)
{
	char	*env_value;
	char	*new_str;
	char	*start_ptr;
	char	*var_with_dollar;

	var_with_dollar = (char *)malloc(ft_strlen(tmp) + 2);
	if (!var_with_dollar)
		error_malloc();
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
		if (!new_str)
			error_malloc();
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
	if (!tmp)
		error_malloc();
	while (str[jdx] && is_alpha_num(str[jdx]))
	{
		tmp[jdx] = str[jdx];
		jdx++;
	}
	tmp[jdx] = '\0';
	return (tmp);
}
