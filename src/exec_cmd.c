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

void	signal_get(int sig_num)
{
	if (sig_num == 2)
	{
	}
}

struct termios org_term;
struct termios new_term;

// void	save_input_mode(void)
// {
// 	tcgetattr(STDIN_FILENO, &org_term); //STDIN으로부터 터미널 속성을 받아온다.
// }

// void	set_input_mode(void)
// {
// 	tcgetattr(STDIN_FILENO, &new_term); //STDIN으로부터 터미널 속성을 받아온다.
// 	new_term.c_lflag &= ~(ICANON | ECHO); //ICANON, ECHO 속성을 off
// 	new_term.c_cc[VMIN] = 1;
// 	new_term.c_cc[VTIME] = 0;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);	
// }

// void	reset_input_mode(void)
// {
// 	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
// }
void signal_handler(int signal_num) {
	(void)signal_num;
	ft_putstr_fd("in", 2);
}

void modify_terminal_settings() {

    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    //new_term.c_lflag |= (ISIG);      // 시그널을 활성화
    new_term.c_lflag &= ~(ECHOCTL | ICANON | ECHO);  // 시그널 문자 출력을 비활성화
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);
}

void	sigint_handler(int signal)
{
	(void)signal;
	global_signal = 1;
	rl_replace_line("", 0);
	write(1, "\n",1);
	rl_on_new_line();
	rl_redisplay();
}

int main(int ac, char **av, char ** envp)
{


	global_signal = 0;
	(void)ac;
	(void)av;
	// struct sigaction	new_act;
	// new_act.sa_flags = 0;
	// sigemptyset(&new_act.sa_mask);
	// new_act.__sigaction_u.__sa_handler = SIG_IGN;
	// sigaction(SIGQUIT, &new_act, NULL);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sigint_handler);
	// save_input_mode(); //터미널 세팅 저장
	// set_input_mode();
	modify_terminal_settings();
	readlilne_tester(envp);
	// save_input_mode(); //터미널 세팅 저장
	// reset_input_mode();
}

void	readlilne_tester(char **envp)
{
	char	*temp;
	t_mini	*node;
	t_env	env;

	env_init(&env, envp);
	//modify_terminal_settings();
	while (1)
	{
		temp = readline("minishell : ");
		if  (!temp)
		{
			ft_putstr_fd("is d", 2);
			break;
		}
		if (*temp)
		{
			parsing(&node, temp);
			exec_cmd(node, &env);
			node_free(node);
			//free(temp);
			//command_free(token);
		}
		else
		{
			printf("press enter\n");
			continue;
		}
		free(temp);
    	signal(SIGQUIT, SIG_IGN);
    	signal(SIGINT, sigint_handler);
		close(0);
		close(1);
		// dup2(node->origin_in, 0);
		// dup2(node->origin_out, 1);
	}
}

// void	process_start2(t_mini *data, t_env *env)
// {
// 	int		i;
// 	int		prev_pipe;
// 	int		cur_pipe[2];
// 	pid_t	pid;

// 	i = -1;
// 	prev_pipe = 0;

// 	while ((++i < data->cnt))
// 	{
// 		//heredoc_ready2(&data[i], env);
// 		pipe(cur_pipe);
// 		pid = fork();
// 		if (pid == 0)
// 		{	
// 			if (data->input_fd == - 1 || data->output_fd == -1)
// 				exit(128);
// 			if (data[i].input_fd)
// 			{
// 				dup2(data[i].input_fd, 0);
// 				close(data[i].input_fd);
// 			}
// 			else if (data[i].cnt > 1 && prev_pipe)
// 			{
// 				dup2(prev_pipe, 0);
// 				close(prev_pipe);
// 			}
// 			else
// 			{
// 				dup2(0, data[i].origin_in);
// 			}
// 			if (data[i].output_fd)
// 			{
// 				dup2(data[i].output_fd, 1);
// 				close(data[i].output_fd);
// 			}
// 			else if (data[i].cnt > 1 && data[i].cnt - 1 != i)
// 			{
// 				close(cur_pipe[0]);
// 				dup2(cur_pipe[1], 1);
// 				close(cur_pipe[1]);
// 			}
// 			else
// 			{
// 				dup2(1, data[i].origin_out);
// 			}
// 			if (!data[i].builtin_cnt && data[i].cmd_size - data[i].delete > 0)
// 			{
// 				cmd_find(&data[i], env);
// 			}
// 			else if (data[i].builtin_cnt == 1)
// 			{
// 				do_builtin(&data[i], env);
// 				exit(0);
// 			}
// 			else
// 				exit(0);
// 		}
// 		else if (pid > 0)
// 		{
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
// 	temp_deleter(data);
// } 

// void	heredoc_ready2(t_mini *data, t_env *env)
// {
// 	int		heredoc;
// 	char	**limmiter;
// 	int		i;
// 	pid_t	id;
// 	int		fd[2];

// 	heredoc = 0;
// 	heredoc = heredoc_counter(data);
// 	limmiter = limmiter_set(data, heredoc);
// 	if (!heredoc)
// 		return ;
// 	pipe(fd);

// 	while (i < heredoc)
// 	{
// 		id = fork();
// 		if (id == 0)
// 		{
// 		}
// 		else if (id > 0)
// 		{
// 			close(fd[1]);
// 			dup2(fd[0], 0);
// 		}
// 		else
// 			error_fork();
// 	}
// }

// char	**limmiter_set(t_mini *data, int heredoc)
// {
// 	char	**ret;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	ret = (char **)malloc(sizeof(char *) *(heredoc + 1));
// 	ret[heredoc] = NULL;
// 	while (++i < data->cmd_size)
// 	{
// 		if (data->command[i] && ft_strcmp("<<", data->command[i]) == 0)
// 		{
// 			ret[j] = ft_strdup(data->command[i + 1]);
// 			set_cmd_null(data, i, i + 1);
// 			j++;
// 		}
// 	}
// 	return (ret);
// }



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

