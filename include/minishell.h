/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:14:11 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/17 14:43:15 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env_node
{
	char	*key;
	char	*value;
} t_env_node;

typedef struct s_env
{
	t_env_node	*node;
	t_env_node	*export;
} t_env;

typedef struct s_mini
{
	char	**command;
} t_mini; 

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

void	dollor_conver(char *str, int *fd, t_env* env);
int	dollar_conver2(int i, t_env *env, char *str, int *fd);
int	dollar_conver3(int i, char *str, int *fd);
#endif