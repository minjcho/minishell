/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:05:25 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 20:37:27 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	file_create(t_mini *data, int i, int flag)
// {
// 	int	fd;

// 	if (i + 1 > data->cmd_size)
// 		exit(258);
// 	if (data->output_fd != 0)
// 		close(data->output_fd);
// 	if (flag)
// 	{
// 		fd = open(data->command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 			error_file(data->command[i + 1]);
// 	}
// 	else
// 	{
// 		fd = open(data->command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 			error_file();
// 	}
// 	data->output_fd = fd;
// 	set_cmd_null(data, i, i + 1);
// }

// void	file_open(t_mini *data, int i)
// {
// 	char	*file_name;
// 	int		fd;

// 	if (i + 1 > data->cmd_size)
// 		exit(258);
// 	if (data->input_fd != 0)
// 	{
// 		close(data->input_fd);
// 	}
// 	file_name = data->command[i + 1];
// 	fd = open (file_name, O_RDONLY);
// 	if (fd == -1)
// 		error_file();
// 	data->input_fd = fd;
// 	set_cmd_null(data, i, i + 1);
// }

void	set_cmd_null(t_mini *data, int start, int end)
{
	char	*temp;

	while (start <= end)
	{
		temp = data->command[start];
		data->command[start] = NULL;
		free(temp);
		data->delete++;
		start++;
	}
}

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i] - s2[i]));
		i++;
	}
	return (0);
}
