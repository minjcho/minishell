/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:06:49 by minjcho           #+#    #+#             */
/*   Updated: 2023/08/24 20:37:13 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_g_signal(char **str, int start_idx)
{
	char	*tmp;
	char	*new_str;
	char	*start_ptr;

	tmp = ft_itoa(g_signal);
	start_ptr = ft_strstr(*str + start_idx, "$?");
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
