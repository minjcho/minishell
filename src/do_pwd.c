/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:34:50 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 14:58:10 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(void)
{
	char	cur_directory[256];

	getcwd(cur_directory, sizeof(cur_directory));
	ft_putstr_fd(cur_directory, 1);
	ft_putstr_fd("\n", 1);
}
