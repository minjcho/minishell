/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:34:50 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 16:45:24 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(void)
{
	char	cur_directory[256];

	if (!getcwd(cur_directory, sizeof(cur_directory)))
	{
		g_signal = 1;
		ft_putstr_fd("pwd: error retrieving current directory:", 2);
		ft_putstr_fd("getcwd: cannot access parent directories:", 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(cur_directory, 1);
		ft_putstr_fd("\n", 1);
	}
}
