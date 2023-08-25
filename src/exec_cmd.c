/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 16:30:19 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	g_signal = 0;
	(void)ac;
	(void)av;
	readlilne_tester(envp);
}

char	*get_user_input(void)
{
	char	*temp;

	signal_main();
	temp = readline("minishell : ");
	if (!temp)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (*temp)
		add_history(temp);
	return (temp);
}

void	process_input(char *temp, t_mini *node, t_env *env)
{
	bool	is_ok;

	is_ok = parsing(&node, temp);
	if (node->cmd_size == 0)
	{
		node_free2(node);
		free(temp);
		return ;
	}
	if (is_ok == true && check_struct(node, env) == false)
		exec_cmd(node, env);
	node_free2(node);
	free(temp);
	temp = NULL;
	close(0);
	close(1);
	dup2(node->origin_in, 0);
	dup2(node->origin_out, 1);
}

void	readlilne_tester(char **envp)
{
	char	*temp;
	t_mini	*node;
	t_env	env;

	node = NULL;
	env_init(&env, envp);
	while (1)
	{
		temp = get_user_input();
		if (*temp)
			process_input(temp, node, &env);
		else
		{
			free(temp);
			continue ;
		}
	}
}
