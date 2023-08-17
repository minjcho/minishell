/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:58:00 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/10 11:23:20 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	error_execve(void)
// {
// 	perror("execve");
// 	exit(1);
// }

void	error_file(char *file)
{
	perror(file);
}

void	error_fork(void)
{
	perror("fork");
	exit(1);
}

void	error_pipe(void)
{
	perror("pipe");
	exit(1);
}

void	error_malloc(void)
{
	perror("malloc");
	exit(1);
}
