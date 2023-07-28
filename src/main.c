/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:33:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/28 13:56:56 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_mini	mini;
	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		printf("%s\n", line);
	}
}
