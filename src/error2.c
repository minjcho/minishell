/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:59:44 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 13:48:46 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmdnotfound(char *cmd)
{
	int			i;
	char		*str;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '/')
			error_cmd2(cmd, i);
	}
	str = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	exit(127);
}

void	error_cmd2(char *cmd, int i)
{
	char		*str;
	struct stat	file_stat;
	int			exitcode;

	exitcode = 0;
	if ((i > 0 && cmd[i - 1] == '.') && lstat(cmd, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			str = ": is a directory\n";
		else
			str = ": Permission denied\n";
		exitcode = 126;
	}
	else if (lstat(cmd, &file_stat) == -1)
	{
		str = ": No such file or directory\n";
		exitcode = 127;
	}
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	exit(exitcode);
}

void	error_export_valid(char *key)
{
	g_signal = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	error_exit(char *str)
{
	g_signal = 1;
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	error_exit2(void)
{
	g_signal = 1;
	ft_putstr_fd("exit: too many arguments\n", 2);
}
