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
	(void)ac;
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
	env.node = (t_env_node *)malloc(sizeof(t_env_node) * 5);
	env.node[0].key = ft_strdup("PWD");
	env.node[0].value = ft_strdup(getenv("PWD"));
	//env.node[0].value = NULL;
	env.node[1].key = ft_strdup("OLDPWD");
	env.node[1].value = NULL;
	env.node[2].key = ft_strdup("HOME");
	//env.node[2].key = NULL;
	env.node[2].value = ft_strdup(getenv("HOME"));
	//env.node[2].value = NULL;
	env.node[3].key = ft_strdup("PATH");
	env.node[3].value = ft_strdup(getenv("PATH"));
	env.node[4].key = NULL;
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
			if (size == 0)
				continue;
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
				node[i].doc_cnt = 0;
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
			{
				dup2(0, data[i].origin_in);
			}
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
			{
				dup2(1, data[i].origin_out);
			}
			if (!data[i].builtin_cnt && data[i].cmd_size - data[i].delete > 0)
			{
				cmd_find(&data[i], env);
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
	//temp_deleter(data);
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

// int	is_equal(char *str)
// {
// 	int	i;

// 	i = -1;
// 	if (str)
// 	{
// 		while (str[i++])
// 		{
// 			if (str[i] == '=')
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

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




// void	do_cd(t_mini *data, t_env *env)
// {
// 	char	*to_directory;
	
// 	to_directory = NULL;
// 	if (data->cmd_size > 1)
// 		to_directory = ft_strdup(data->command[1]);
// 	if (to_home_directory(to_directory))
// 	{
// 		free(to_directory);
// 		to_directory = ft_getenv("HOME", env);
// 	}
// 	else if (to_back_directory(to_directory))
// 	{
// 		free(to_directory);
// 		to_directory = ft_getenv("OLDPWD", env);
// 		if (!to_directory)
// 		{
// 			error_oldpath_not_set();
// 			return ;
// 		}
// 	}
// 	do_cd2(to_directory, data, env);
// }

// void	do_cd2(char *to_directory, t_mini *data, t_env *env)
// {
// 	char	full_direcotry[256];
// 	char	*temp;

// 	if (getcwd(full_direcotry, sizeof(full_direcotry)) != NULL)
// 	{
// 		temp = ft_strdup(full_direcotry);
// 		ft_setenv("OLDPWD", temp, env);
// 		free(temp);
// 	}
// 	if(chdir(to_directory) == -1)
// 	{
// 		perror(data->command[1]);
// 		return ;
// 	}
// 	if (getcwd(full_direcotry, sizeof(full_direcotry)) != NULL)
// 	{
// 		// temp = ft_getenv("PWD", env);
// 		// free(temp);
// 		temp = ft_strdup(full_direcotry);
// 		ft_setenv("PWD", temp, env);
// 		free(temp);
// 	}
// 	free(to_directory);
// }

// int	is_argument(char **command, t_mini *data)
// {
// 	int	i;
// 	int	is_argument;

// 	i = -1;
// 	is_argument = 0;
// 	while (++i < data->cmd_size)
// 	{
// 		if (data->command[i] == NULL)
// 			continue;
// 		else if (ft_strncmp("-", data->command[i], 1) != 0)
// 			is_argument++;
// 	}
// 	if (is_argument > 1)
// 		return (1);
// 	return (0);
// }

// void	cmd_start(t_mini *data, char **split_path)
// {
// 	char	*slash_join;
// 	char	*cmd;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (split_path && split_path[++i])
// 	{
// 		slash_join = ft_strjoin(split_path[i], "/");
// 		j = -1;
// 		while (++j < data->cmd_size)
// 		{
// 			if (data->command[j] != NULL)
// 			{
// 				cmd = ft_strjoin(slash_join, data->command[j]);
// 				if (access(cmd, X_OK) == 0)
// 				{
// 					command_realloc(data);
// 					if (execve(cmd, data->command, NULL) == -1)
// 						error_execve();
// 				}
// 				free(cmd);
// 			}
// 		}
// 		free(slash_join);
// 	}
// 	error_cmdnotfound(data->command[0], data);
// }

