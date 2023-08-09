/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:59:44 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/08 16:07:39 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_path_not_set(char *path_name)
{
	char	*str;
	char	*str1;

	str = "cd: ";
	str1 = " not set\n";
	write(2, str, ft_strlen(str));
	write(2, path_name, ft_strlen(path_name));
	write(2, str1, ft_strlen(str1));
}

void	error_cmdnotfound(char *cmd, t_mini *data)
{
	char	*str;

	(void)data;
	str = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	exit(128);
}

void	error_export_valid(char *key)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}