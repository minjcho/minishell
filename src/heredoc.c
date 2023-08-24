/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:17:33 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/24 21:20:56 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(char *limiter, int *fd, t_env *env)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, limiter) == 0)
		{
			free(limiter);
			free(str);
			close(fd[1]);
			exit(0);
		}
		if (dollar_counter(str))
			dollor_conver(str, fd, env);
		else
		{
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
		}
		free(str);
	}
}

int	dollar_counter(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '$')
			cnt++;
		i++;
	}
	return (cnt);
}

void	dollor_conver(char *str, int *fd, t_env *env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
				write(fd[1], &str[i], 1);
			else if (str[i + 1] == '?')
			{
				write(fd[1], ft_itoa(g_signal), \
						ft_strlen(ft_itoa(g_signal)));
				i++;
			}
			else if (str[i + 1] == '$')
				i += dollar_conver3(i, str, fd);
			else if (str[i + 1])
				i += dollar_conver2(i, env, str, fd);
		}
		else
			write(fd[1], &str[i], 1);
	}
	write(fd[1], "\n", 1);
}

int	dollar_conver3(int i, char *str, int *fd)
{
	int	j;

	j = i;
	while (str[j])
	{
		if (str[j] != '$')
			break ;
		write(fd[1], &str[j], 1);
		j++;
	}
	return (j - i - 1);
}

int	dollar_conver2(int i, t_env *env, char *str, int *fd)
{
	int		j;
	char	*environ;
	char	*env_val;

	j = i + 1;
	env_val = NULL;
	while (str[j])
	{
		if (str[j] == ' ' || !str[j] || str[j] == '$' \
			|| str[j] == '\"' || str[j] == '\'')
			break ;
		j++;
	}
	environ = ft_substr(str, i + 1, j - i - 1);
	env_val = ft_getenv(environ, env);
	write(fd[1], env_val, ft_strlen(env_val));
	free(environ);
	return (j - i - 1);
}
