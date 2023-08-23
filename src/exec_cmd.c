/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/23 13:54:32 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	global_signal = 0;
	(void)ac;
	(void)av;
	readlilne_tester(envp);
}

void	readlilne_tester(char **envp)
{
	char	*temp;
	t_mini	*node;
	t_env	env;

	env_init(&env, envp);
	while (1)
	{
		signal_main();
		temp = readline("minishell : ");
		if (!temp)
			exit(0);
		if (*temp)
		{
			add_history(temp);
			parsing(&node, temp);
			if (check_struct(node, &env) == false)
				exec_cmd(node, &env);
			node_free2(node);
		}
		else
			continue ;
		free(temp);
		close(0);
		close(1);
		dup2(node->origin_in, 0);
		dup2(node->origin_out, 1);
	}
}
