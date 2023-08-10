/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:27:15 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/09 21:59:07 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_counter(t_mini *data)
{
	int	i;
	int	j;
	int	cnt;

	i = -1;
	cnt = 0;
	while (++i < data->cnt)
	{
		j = 0;
		while (j < data[i].cmd_size)
		{
			if (ft_strcmp("<<", data[i].command[j]) == 0)
			{
				cnt++;
			}
			j++;
		}
	}
	return (cnt);
}

// char	*set_temp_file(t_mini *data, int k)
// {
// 	int		i;
// 	int		fd;
// 	char	*temp_num;
// 	char	*res_path;
// 	char	*temp_file;
// 	(void)data;

// 	i = 0;
// 	res_path = "/Users/jinhyeok/goinfre/temp";
// 	while (1)
// 	{
// 		temp_num = ft_itoa(k + i);
// 		temp_file = ft_strjoin(res_path, temp_num);
// 		fd = open(temp_file, O_RDONLY);
// 		if (fd > 0)
// 		{
// 			close(fd);
// 			free(temp_file);
// 			free(temp_num);
// 		}
// 		else
// 			break ;
// 		i++;
// 	}
// 	free(temp_num);
// 	return (temp_file);
// }

// void	do_heredoc(t_mini *data, char **limmiter, char **temp_files)
// {
// 	int		i;
// 	pid_t	id;
// 	int		fd;
// 	char	*str;

// 	i = -1;
// 	fd = 0;
// 	(void)data;
// 	while (limmiter[++i])
// 	{
// 		id = fork();
// 		if (id == 0)
// 		{
// 			ft_putstr_fd(temp_files[i], 2);
// 			fd = open(temp_files[i], O_WRONLY | O_CREAT, 0644);
// 			if (fd == -1)
// 				error_file();
// 			while (1)
// 			{
// 				str = readline("> ");
// 				if (!str || ft_strcmp(str, limmiter[i]) == 0)
// 					break ;
// 				write(fd, str, ft_strlen(str));
// 				write(fd, "\n", 1);
// 				free(str);
// 			}
// 			close (fd);
// 		}
// 		else if (id > 0)
// 		{
// 			wait(NULL);
// 		}
// 		else
// 			error_fork();
// 	}
// }

// void	heredoc_ready(t_mini *data, t_env *env)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*temp;
// 	char	**temp_files;
// 	char	**limmiter;
// 	int		heredoc;

// 	i = -1;
// 	(void)env;
// 	heredoc = 0;
// 	while (++i < data->cnt)
// 	{
// 		heredoc = heredoc_counter(&data[i]);
// 		if (!heredoc)
// 			continue;
// 		limmiter = (char **)malloc(sizeof(char *) * (heredoc + 1));
// 		temp_files = (char **)malloc(sizeof(char *) * (heredoc + 1));
// 		if (!limmiter)
// 			error_malloc();
// 		limmiter[heredoc] = NULL;
// 		temp_files[heredoc] = NULL;
// 		j = 0;
// 		k = 0;
// 		while (data[i].command[j])
// 		{
// 			if (data[i].command[j] && ft_strcmp("<<", data[i].command[j]) == 0)
// 			{
// 				temp = data[i].command[j];
// 				data[i].command[j] = ft_strdup("<");
// 				free(temp);
// 				limmiter[k] = data[i].command[j + 1];
// 				data[i].command[j + 1] = set_temp_file(data, k);
// 				temp_files[k] = ft_strdup(data[i].command[j + 1]);
// 				k++;
// 			}
// 			j++;
// 		}
// 		data[i].temp_files = temp_files;
// 		if (heredoc)
// 		{
// 			data->doc_cnt = 1;
// 			do_heredoc(data, limmiter, temp_files);
// 		}
// 	}
// }
