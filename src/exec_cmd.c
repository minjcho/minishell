/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/28 14:18:27 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char ** envp)
{
	t_mini	**data;
	
	data = (t_mini **)malloc(sizeof(t_mini *) * 2);
	data[0] = (t_mini *)malloc(sizeof(t_mini));
	data[0]->command = (char **)malloc(sizeof(char *) * 4);
	data[0]->command[0] = "<";
	data[0]->command[1] = "test";
	data[0]->command[2] = "cat";
	data[0]->command[3] = NULL;
	data[1] = NULL;
	
	exec_cmd(data); 
}

void	exec_cmd(t_mini **data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		redirection_set(data[i]);
	}
}

int	redirection_set(t_mini *data)
{
	int	i;

	i = -1;
	while (data->command[++i])
	{
		if (ft_str)


	}
}

