/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:06:49 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/23 13:07:00 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_global_signal(char **str)
{
	char	*tmp;
	char	*new_str;
	char	*start_ptr;

	tmp = ft_itoa(global_signal);
	start_ptr = ft_strstr(*str, "$?");
	if (start_ptr)
	{
		new_str = (char *)malloc(ft_strlen(*str) - \
								ft_strlen("$?") + ft_strlen(tmp) + 1);
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
	int		i;
	int		j;
	int		k;
	bool	did_replace;

	i = -1;
	while ((*mini)[++i].command)
	{
		j = -1;
		while ((*mini)[i].command[++j])
		{
			k = -1;
			while ((*mini)[i].command[j][++k] && (*mini)[i].command[j][k + 1])
			{
				if ((*mini)[i].command[j][k] == '$' && \
					(*mini)[i].command[j][k + 1] == '?' && \
					(*mini)[i].command[j][0] != '\'')
				{
					did_replace = true;
					put_global_signal(&(*mini)[i].command[j]);
				}
			}
		}
	}
	return (did_replace);
}

char	*remove_quotation_from_str(char *str)
{
	int		len;
	char	*trimmed_str;

	len = ft_strlen(str);
	if (str[0] == '\'' && str[len - 1] == '\'' && len > 2)
	{
		trimmed_str = ft_strtrim(str, "\'");
		free(str);
		return (trimmed_str);
	}
	else if (str[0] == '\'' && str[len - 1] == '\'' && len == 2)
	{
		free(str);
		return (ft_strdup(""));
	}
	return (str);
}

void	remove_single_quotation_from_mini(t_mini *mini)
{
	int		idx;
	int		jdx;

	idx = -1;
	while (mini[++idx].command)
	{
		jdx = -1;
		while (++jdx < mini[idx].cmd_size)
		{
			mini[idx].command[jdx] = \
				remove_quotation_from_str(mini[idx].command[jdx]);
		}
	}
}

void	remove_single_quotation(t_mini *mini)
{
	bool	did_replace;

	did_replace = replace_dollar_question(&mini);
	remove_single_quotation_from_mini(mini);
	if (did_replace)
		global_signal = 0;
}
