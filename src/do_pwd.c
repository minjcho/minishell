/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:34:50 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:35:02 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(t_mini *data, t_env *env)
{
	char *temp;

	temp = ft_getenv("PWD", env);
	write(1, temp, ft_strlen(temp));
	write(1, "\n", 1);
}