/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:14:16 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/02 16:29:52by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	leaks(void)
{
	system("leaks a.out");
}
int	origin_in;
int	origin_out;

extern char **environ;

int main(int ac, char **av, char ** envp)
{
	readlilne_tester();
}

void	readlilne_tester(void)
{
	char	*temp;
	char	**token;
	char	**to_cmmand;
	int		i;
	int		origin_in;
	int		origin_out;
	t_mini	*node;
	t_env	env;

	node = NULL;
	env.node = (t_env_node *)malloc(sizeof(t_env_node) * 4);
	env.node[0].key = ft_strdup("PWD");
	env.node[0].value = ft_strdup(getenv("PWD"));
	env.node[1].key = ft_strdup("OLDPWD");
	env.node[1].value = NULL;
	env.node[2].key = ft_strdup("HOME");
	env.node[2].value = ft_strdup(getenv("HOME"));
	env.node[3].key = NULL;
	origin_in = dup(0);
	origin_out = dup(1);
	env.export = (t_env_node *)malloc(sizeof(t_env_node) * 6);
	env.export[0].key = ft_strdup("PWD");
	env.export[0].value = ft_strdup(getenv("PWD"));
	env.export[1].key = ft_strdup("A");
	env.export[1].value = NULL;
	env.export[2].key = ft_strdup("BBbb");
	env.export[2].value = NULL;
	env.export[3].key = ft_strdup("a");
	env.export[3].value = NULL;
	env.export[4].key = ft_strdup("AAA");
	env.export[4].value = NULL;
	env.export[5].key = NULL;
	while (1)
	{
		temp = readline("minishell : ");
		if (temp)
		{
			token = ft_split(temp, '|');
			int	i = 0;
			int	size = 0;
			while (token[i])
				i++;
			size = i;
			node = (t_mini *)malloc(sizeof(t_mini) * i);
			i = -1;
			while (token[++i])
			{
				to_cmmand = ft_split(token[i], ' ');
				node[i].command = to_cmmand;
				node[i].cnt = size;
				node[i].input_fd = 0;
				node[i].output_fd = 0;
				node[i].origin_in = origin_in;
				node[i].origin_out = origin_out;
				node[i].delete = 0;
				int	j = 0;
				while (to_cmmand[j])
					j++;
				node[i].cmd_size = j;
			}
			// int	k = -1;
			// while (++k < node->cnt)
			// {
			// 	for (int i = 0 ; i < node[k].cmd_size ; i++)
			// 	{
			// 		printf("%s\n", node[k].command[i]);
			// 	}
			// 	printf("------------------\n");
			// }
			free(temp);
			exec_cmd(node, &env);
			node_free(node);
			command_free(token);
		}
	}
}

void	node_free(t_mini *node)
{
	int	i;

	i = -1;
	if (node)
	{
		while (++i < node->cnt)
		{
			if (&node[i])
			{
				command_free(node[i].command);
			}
		}
		free(node);
	}
}

void	process_start2(t_mini *data, t_env *env)
{
	int		i;
	int		prev_pipe;
	int		cur_pipe[2];
	pid_t	pid;

	i = -1;
	prev_pipe = 0;

	while ((++i < data->cnt))
	{
		pipe(cur_pipe);
		pid = fork();
		if (pid == 0)
		{	
			if (data->input_fd == - 1 || data->output_fd == -1)
				exit(128);
			if (data[i].input_fd)
			{
				dup2(data[i].input_fd, 0);
				close(data[i].input_fd);
			}
			else if (data[i].cnt > 1 && prev_pipe)
			{
				dup2(prev_pipe, 0);
				close(prev_pipe);
			}
			else
				dup2(0, data[i].origin_in);
			if (data[i].output_fd)
			{
				dup2(data[i].output_fd, 1);
				close(data[i].output_fd);
			}
			else if (data[i].cnt > 1 && data[i].cnt - 1 != i)
			{
				close(cur_pipe[0]);
				dup2(cur_pipe[1], 1);
				close(cur_pipe[1]);
			}
			else
				dup2(1, data[i].origin_out);
			if (!data[i].builtin_cnt && data[i].cmd_size - data[i].delete > 0)
			{
				cmd_find(&data[i]);
			}
			else if (data[i].builtin_cnt == 1)
			{
				do_builtin(&data[i], env);
				exit(0);
			}
			else
				exit(0);
		}
		else if (pid > 0)
		{
			close(cur_pipe[1]);
			if (prev_pipe)
				close(prev_pipe);
			if (data[i].cnt > 1)
				prev_pipe = cur_pipe[0];
			else
				close(cur_pipe[0]);
		}
		else
			error_fork();
	}
	while (i)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
} 

// void	process_start2(t_mini *data)
// {
// 	int		i;
// 	int		prev_pipe;
// 	int		cur_pipe[2];
// 	pid_t	pid;

// 	i = -1;
// 	prev_pipe = 0;

// 	while ((++i < data->cnt))
// 	{
	
// 		pipe(cur_pipe);
// 		pid = fork();
// 		if (pid == 0)
// 		{	
// 			if (data->input_fd == - 1 || data->output_fd == -1)
// 				exit(128);
// 			// if (is_argument(data[i].command, &data[i]))
// 			// {
// 			// 	ft_putstr_fd("1", 2);
// 			// 	if (data[i].input_fd)
// 			// 		close(data[i].input_fd);
// 			// 	data[i].input_fd = 0;
// 			// }
// 			if (data[i].input_fd != 0)
// 			{
// 				ft_putstr_fd("2", 2);
// 				if (dup2(data[i].input_fd, 0) == -1)
// 					write(2, "in", 2);
// 				close(data[i].input_fd);
// 			}
// 			if (prev_pipe)
// 			{
// 				ft_putstr_fd("3", 2);
// 				dup2(prev_pipe, 0);
// 				close(prev_pipe);
// 			}
// 			if (data[i].cnt > 1 && data[i].cnt - 1 != i)
// 			{
// 				ft_putstr_fd("4", 2);
// 				close(cur_pipe[0]);
// 				dup2(cur_pipe[1], 1);
// 				close(cur_pipe[1]);
// 			}
// 			if (data[i].output_fd != 0)
// 			{
// 				ft_putstr_fd("5", 2);
// 				dup2(data[i].output_fd, 1);
// 				close(data[i].output_fd);
// 			}
// 			if (!data[i].builtin_cnt)
// 			{
// 				ft_putstr_fd("6", 2);
// 				cmd_find(&data[i]);
// 			}
// 			else
// 			{
// 				ft_putstr_fd("7", 2);
// 				do_builtin(&data[i]);
// 				exit(0);
// 			}
// 		}
// 		else if (pid > 0)
// 		{
// 			// if (data->builtin_cnt == 1)
// 			// {
// 			// 	do_builtin(data);
// 			// 	break;
// 			// }
// 			close(cur_pipe[1]);
// 			if (prev_pipe)
// 				close(prev_pipe);
// 			if (data[i].cnt > 1)
// 				prev_pipe = cur_pipe[0];
// 			else
// 				close(cur_pipe[0]);
// 		}
// 		else
// 			error_fork();
// 	}
// 	while (i)
// 	{
// 		waitpid(-1, NULL, 0);
// 		i--;
// 	}
// }

void	builtin_counter(t_mini *data)
{
	int	i;
	int	builtin_cnt;

	i = -1;
	builtin_cnt = 0;
	while (++i < data->cnt)
	{
		builtin_cnt = 0;
		if (builtin_check(&data[i]))
			builtin_cnt++;
		data[i].builtin_cnt = builtin_cnt;
	}
}

int	builtin_check(t_mini *data)
{
	char	*temp;

	if (data->command[0])
	{
		temp = data->command[0];
		if (ft_strncmp(temp, "cd", ft_strlen(temp)) == 0)
			return (1);
		else if (ft_strncmp(temp, "echo", ft_strlen(temp)) == 0)
			return (2);
		else if (ft_strncmp(temp, "pwd", ft_strlen(temp)) == 0)
			return (3);
		else if (ft_strncmp(temp, "export", ft_strlen(temp)) == 0)
			return (4);
		else if (ft_strncmp(temp, "unset", ft_strlen(temp)) == 0)
			return (5);
		else if (ft_strncmp(temp, "env", ft_strlen(temp)) == 0)
			return (6);
		else if (ft_strncmp(temp, "exit", ft_strlen(temp)) == 0)
			return (7);
	}
	return (0);
}

void	do_builtin(t_mini *data, t_env *env)// seperate input &data[i];
{
	if (builtin_check(data) == 1) // need update evn val
		do_cd(data, env);
	else if (builtin_check(data) == 2)
		do_echo(data);
	else if (builtin_check(data) == 3)
		do_pwd(data, env);
	else if (builtin_check(data) == 4)
		do_export(data, env);
	else if (builtin_check(data) == 6)
		do_env(env);
	else if (builtin_check(data) == 7)
		do_exit(data);
}

void	do_export(t_mini *data, t_env *env)
{
	if (data->command[1] == NULL)
		export_print(env);
	else if (data->command[1])
	{
		export_val(data, env);
	}
}

void	export_val(t_mini *data, t_env *env)
{
	int		i;
	char	*key;
	char	*value;
	char	**temp;

	i = 0;
	key = NULL;
	value = NULL;
	while (data->command[++i])
	{
		temp = ft_split(data->command[i], '=');
		key = temp[0];
		value = temp[1];
		if (!value)
			ft_setexport(key, value, env);
		else
		{
			ft_setexport(key, value, env);
			ft_setenv(key, value, env);
		}
		command_free(temp);
	}
}

t_env_node	*realloc_evnode(char *key, char *value, t_env_node *node, int flag)
{
	// flag 1 => pluse. flag = -1 minus
	int			new_len;
	t_env_node	*new_node;

	new_len = ft_envlen(node) + flag;
	new_node = (t_env_node *)malloc(sizeof(t_env_node) * (new_len + 1));
	if (!new_node)
		error_malloc();
	new_node[new_len].key = NULL;
	if (flag == -1)
		ft_nodecpy(new_node, node, key);
	else
	{
		ft_nodecpy(new_node, node, NULL);
		if (key)
			new_node[new_len - 1].key = ft_strdup(key);
		else
			new_node[new_len - 1].key = NULL;
		if (value)
			new_node[new_len - 1].value = ft_strdup(value);
		else
			new_node[new_len - 1].value = NULL;
	}
	return (new_node);
}

void	ft_setexport(char *key, char *value, t_env *env)
{
	int			i;
	t_env_node	*temp;

	i = -1;
	while (env->export[++i].key)
	{
		if (ft_strncmp(key, env->export[i].key, ft_strlen(key)) == 0)
		{
			env->export[i].value = value;
			return ;
		}
	}
	temp = env->export;
	env->export = realloc_evnode(key, value, temp, 1);
	env_free(temp);
}

void	ft_setenv(char *key, char *value, t_env *env)
{
	int			i;
	t_env_node	*temp;

	i = -1;
	while (env->node[++i].key)
	{
		if (ft_strncmp(key, env->node[i].key, ft_strlen(key)) == 0)
		{
			free(env->node[i].value);
			env->node[i].value = value;
			return ;
		}
	}
	temp = env->node;
	env->node = realloc_evnode(key, value, temp, 1);
	env_free(temp);
}

// void	ft_setenv(char *key, char *value, t_env *env)
// {
// 	int		i;
// 	char	*temp;

// 	i = -1;
// 	temp = NULL;
// 	while (env->node[++i].key)
// 	{
// 		if (ft_strncmp(key, env->node[i].key, ft_strlen(key)) == 0)
// 		{
// 			if (env->node[i].value)
// 				temp = env->node[i].value;
// 			env->node[i].value = ft_strdup(value);
// 			if (temp)
// 				free(temp);
// 			return ;
// 		}
// 	}// need realloc; if the key val is not in here, make the new keyvalue
// 	//realloc_set(key, value, 0);
// }

void	env_free(t_env_node *node)
{
	int	i;

	i = -1;
	if (node)
	{
		while (node[++i].key)
		{
			free(node[i].key);
			free(node[i].value);
		}
		free(node);
	}
}

void	ft_nodecpy(t_env_node *new_node, t_env_node *old, char *delete)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = ft_envlen(old);
	while (++i < len)
	{
		if (delete != NULL && ft_strncmp(delete, old[i].key, ft_strlen(delete)) == 0)
			continue;
		if (old[i].key)
			new_node[j].key = ft_strdup(old[i].key);
		else
			new_node[j].key = NULL;
		if (old[i].value)
			new_node[j].value = ft_strdup(old[i].value);
		else
			new_node[j].value = NULL;
		j++;
	}
}

// need to be check
// void	ft_set_envexoprt(char *key, char *value, t_env *node)
// {
// 	int		i;
// 	char	*temp;

// 	i = -1;
// 	temp = NULL;
// 	while (node[++i].key)
// 	{
// 		if (ft_strncmp(key, node[i].key, ft_strlen(key)) == 0)
// 		{
// 			if (node[i].value)
// 				temp = node[i].value;
// 				node[i].value = ft_strdup(value);
// 			if (temp)
// 				free(temp);
// 			return ;
// 		}
// 	}// need realloc; if the key val is not in here, make the new keyvalue
// 	realloc_add(key, value, node);
// }

// void	realloc_add(char *key, char *value, t_env_node *node)
// {
// 	int			cur_len;
// 	t_env_node	*node;

// 	cur_len = ft_envlen(node);
// 	if (cur_len)
// 	{


// 	}
// }

// void	realloc_sub(char *key, char *value, t_env_node *node)
// {

// }

int	is_equal(char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[i++])
		{
			if (str[i] == '=')
				return (1);
		}
	}
	return (0);
}

void	export_print(t_env *env)
{
	int		i;
	char	*temp;

	i = -1;
	temp = "declare -x ";
	if (env->export)
	{
		export_sorting(env);
		while (env->export[++i].key)
		{
			write(1, temp, ft_strlen(temp));
			write(1, env->export[i].key, ft_strlen(env->export[i].key));
			if (env->export[i].value)
			{
				write(1, "=\"", 2);
				write(1, env->export[i].value, ft_strlen(env->export[i].value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
	}
}

void	export_sorting(t_env *env)
{
	int	i;
	int	j;
	char	*k1;
	char	*k2;
	t_env_node temp;

	i = -1;
	while (env->export[++i].key)
	{
		j = i + 1;
		while (env->export[j].key)
		{
			k1 = env->export[i].key;
			k2 = env->export[j].key;
			if (ft_strncmp(k1, k2, ft_strlen(k1)) > 0)
			{
				temp.key = k1;
				temp.value = env->export[i].value;
				env->export[i].key = env->export[j].key;
				env->export[i].value = env->export[j].value;
				env->export[j].key = temp.key;
				env->export[j].value = temp.value;
			}
			j++;
		}
	}
}

int	ft_envlen(t_env_node *node)
{
	int			i;
	int			cnt;

	i = -1;
	cnt = 0;
	if (node->key)
	{
		while (node[++i].key)
			cnt++;
	}
	return (cnt);
}

void	do_exit(t_mini *data)
{
	exit(0); // need to free??
}

void	do_env(t_env *env)
{
	int		i;
	char	*k_temp;
	char	*v_temp;

	i = -1;
	if (env->node)
	{
		while (env->node[++i].key)
		{
			k_temp = env->node[i].key;
			v_temp = env->node[i].value;
			write(1, k_temp, ft_strlen(k_temp));
			write(1, "=", 1);
			write(1, v_temp, ft_strlen(v_temp));
			write(1, "\n", 1);
		}
	}
}

// void	do_export(t_mini *data)
// {
// 	int	i;

// 	i = 0;
// 	if (data->command[1])
// 	{
// 		// add all export
// 	}
// 	else
// 	{
// 		// need to sort following ascii (ASD);
// 		// export a cant see in env, export a=1 can see in env;
// 		//show all export members
// 	}
// }

void	do_pwd(t_mini *data, t_env *env)
{
	char *temp;

	temp = ft_getenv("PWD", env);
	write(1, temp, ft_strlen(temp));
	write(1, "\n", 1);
}

void	do_echo(t_mini *data)
{
	int		option_idx;
	char	*new_line;
	int		temp;
	int		i;

	i = 0;
	// if (data->output_fd)
	// 	temp = data->output_fd;
	// else 
		temp = 1;
	option_idx = is_echo_option(data);
	if (option_idx > 1)
	{
		while (option_idx < data->cmd_size)
		{
			write(temp, data->command[option_idx], \
			ft_strlen(data->command[option_idx]));
			write(temp, " ", 1);
			option_idx++;
		}
	}
	else
	{
		while (option_idx < data->cmd_size)
		{
			write(temp, data->command[option_idx], \
			ft_strlen(data->command[option_idx]));
			write(temp, " ", 1);
			option_idx++;
		}
		write(temp, "\n", 1);
	}
}

int	is_echo_option(t_mini *data)
{
	int	i;
	int	j;

	i = 0;
	while(data->command[++i])
	{
		j = 0;
		if (data->command[i][j] == '-')
		{
			while (data->command[i][++j])
			{
				if (data->command[i][j] != 'n')
					return (i);
			}
		}
		else
			return (i);
	}
	return (i);
}



// void	realloc_set(char *key, char *value, int flag)
// {
// 	t_env_node *new_one;

// 	new_one = (t_env_node *)malloc(sizeof(t_env_node) * ft_envlen(flag));

// }


// void	do_cd(t_mini *data)
// {
// 	char	*to_directory;
// 	int		flag;
	
// 	to_directory = NULL;
// 	flag = 0;
// 	if (data->cmd_size > 1)
// 		to_directory = data->command[1];
// 	if (to_home_directory(to_directory))
// 		to_directory = ft_getenv("HOME");
// 	else if (to_back_directory(to_directory))
// 		to_directory = ft_getenv("OLDPWD");
// 	else
// 	{
// 		flag = 1;
// 		if(chdir(to_directory) == -1)
// 		{
// 			perror(data->command[1]);
// 			return ;
// 		}
// 	}
// 	if (flag)
// 		ft_setenv("PWD", to_directory);
// 	else
// 	{

// 	}
// }

void	do_cd(t_mini *data, t_env *env)
{
	char	*to_directory;
	char	full_direcotry[256];
	
	to_directory = NULL;
	if (data->cmd_size > 1)
		to_directory = data->command[1];
	if (to_home_directory(to_directory))
		to_directory = ft_getenv("HOME", env);
	else if (to_back_directory(to_directory))
	{
		to_directory = ft_getenv("OLDPWD", env);
		if (!to_directory)
		{
			error_oldpath_not_set();
			return ;
		}
	}
	do_cd2(to_directory, data, env);
}

void	do_cd2(char *to_directory, t_mini *data, t_env *env)
{
	char	full_direcotry[256];

	if (getcwd(full_direcotry, sizeof(full_direcotry)) != NULL)
		ft_setenv("OLDPWD", ft_strdup(full_direcotry), env);
	if(chdir(to_directory) == -1)
	{
		perror(data->command[1]);
		return ;
	}
	if (getcwd(full_direcotry, sizeof(full_direcotry)) != NULL)
		ft_setenv("PWD", ft_strdup(full_direcotry), env);
}

char	*ft_getenv(char *key, t_env *env)
{
	int	i;

	i = -1;
	if (env->node)
	{
		while (env->node[++i].key)
		{
			if (ft_strncmp(key, env->node[i].key, ft_strlen(key)) == 0)
			{
				return (env->node[i].value);
			}
		}
	}
	return (NULL);
}

int	to_back_directory(char *to_directory)
{
	if (ft_strncmp(to_directory, "-", ft_strlen(to_directory)) == 0)
		return (1);
	else
		return (0);
}

int	to_home_directory(char *to_directory)
{
	if (!to_directory)
		return (1);
	if (!ft_strncmp(to_directory, "~", ft_strlen(to_directory)))
		return (1);
	return (0);
}

int	is_argument(char **command, t_mini *data)
{
	int	i;
	int	is_argument;

	i = -1;
	is_argument = 0;
	while (++i < data->cmd_size)
	{
		if (data->command[i] == NULL)
			continue;
		else if (ft_strncmp("-", data->command[i], 1) != 0)
			is_argument++;
	}
	if (is_argument > 1)
		return (1);
	return (0);
}

void	cmd_find(t_mini *data)
{
	char	*temp;
	char	**split_path;
	
	temp = getenv("PATH");
	split_path = ft_split(temp, ':');
	cmd_start(data, split_path);
}

void	cmd_start(t_mini *data, char **split_path)
{
	char	*slash_join;
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	while (split_path[++i])
	{
		slash_join = ft_strjoin(split_path[i], "/");
		j = -1;
		while (++j < data->cmd_size)
		{
			if (data->command[j] != NULL)
			{
				cmd = ft_strjoin(slash_join, data->command[j]);
				if (access(cmd, X_OK) == 0)
				{
					command_realloc(data);
					if (execve(cmd, data->command, NULL) == -1)
					{
						error_execve();
					}
				}
				free(cmd);
			}
		}
		free(slash_join);
	}
	error_cmdnotfound(data->command[0], data);
}

void	command_realloc(t_mini *data)
{
	int		i;
	int		j;
	int		token_cnt;
	char	**new_token;

	i = -1;
	token_cnt = 0;
	if (data)
	{
		if (data->command)
		{
			while (++i < data->cmd_size)
			{
				if (data->command[i])
					token_cnt++;
			}
		}
	}
	else if (!data || !data->command) 
		return ;
	new_token = (char **)malloc(sizeof(char *) * (token_cnt + 1));
	if (!new_token)
		error_malloc();
	new_token[token_cnt] = NULL;
	i = -1;
	j = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i])
			new_token[++j] = ft_strdup(data->command[i]);
	}
	command_free(data->command);
	data->command = new_token;
}

void	command_free(char **command)
{
	int	i;

	i = -1;
	if (command)
	{
		while (command[++i])
			free(command[i]);
		free(command);
	}
}

void	exec_cmd(t_mini *data, t_env *env)
{
	int	i;

	i = -1;
	while (++i < data[0].cnt)
	{
		redirection_ready(&data[i]);
	}
	builtin_counter(data);
	if (data->builtin_cnt == 1 && data->cnt == 1)
	{
		// redirection
		if (data->input_fd)
		{
			dup2(data->input_fd, 0);
			close(data->input_fd);
		}
		if (data->output_fd)
		{
			dup2(data->output_fd, 1);
			close(data->output_fd);
		}
		do_builtin(data, env);
		dup2(data->origin_in, 0);
		dup2(data->origin_out, 1);
		return ;
	}
	process_start2(data, env);
}

int	redirection_ready(t_mini *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_size)
	{
		if (data->command[i] && is_redirection(data->command[i]))
		{
			set_redirection(data, i);
		}
	}
	return (0);
}

// file open and redirection fd set; 
void    set_redirection(t_mini *data, int i)
{
	if (!data->command[i])
		return ;
	if (is_redirection(data->command[i]) == 1)
		file_open(data, i);
	else if (is_redirection(data->command[i]) == 2)
		file_create(data, i, 0);
	else if (is_redirection(data->command[i]) == 3)
		file_create(data, i, 1);
}

int is_redirection(char *str)
{
	// < > >> <>(?)
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (2);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (3);
	return (0);
}

void    file_create(t_mini *data, int i, int flag)
{
	int fd;

	if (i + 1 > data->cmd_size) // this condition need to be handle in parsing part
		exit(258);
	if (data->output_fd != 0)
		close(data->output_fd);
	if (flag)
	{    
		fd = open(data->command[i + 1],  O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			error_file();
	}
	else 
	{
		fd = open(data->command[i + 1],  O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			error_file();
	}
	data->output_fd = fd;
	set_cmd_null(data, i, i + 1);
}

void    file_open(t_mini *data, int i)
{
	char    *file_name;
	int     fd;

	if (i + 1 > data->cmd_size)
		exit(258);
	if (data->input_fd != 0)
	{
		close(data->input_fd);
	}
	file_name = data->command[i + 1];
	fd = open (file_name, O_RDONLY);
	if (fd == -1)
		error_file();
	data->input_fd = fd;
	set_cmd_null(data, i, i + 1);
}

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
//error msg
void	error_oldpath_not_set(void)
{
	char	*str;

	str = "cd: OLDPWD not set\n";
	write(2, str, ft_strlen(str));
}

void	error_cmdnotfound(char *cmd, t_mini *data)
{
	char	*str;

	str = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	exit(128);
}

void	error_execve(void)
{
	perror("execve");
	exit(1);
}

void    error_file(void)
{
	perror("file");
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
