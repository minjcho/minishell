/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:14:11 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/16 20:12:11 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env_node
{
	char	*key;
	char	*value;
} t_env_node;

typedef struct s_env
{
	t_env_node	*node;
	t_env_node	*export;
} t_env;

typedef struct s_mini
{
	char	**command;
	int		doc_cnt;
	int		cmd_size;
	int		delete;
	int		output_fd;
	int		input_fd;
	int		origin_in;
	int		origin_out;
	int		cnt;
	int		is_heredoc;
	int		builtin_cnt;
} t_mini; 

typedef struct  s_params
{
    t_mini      *data;
    t_env       *env;
    int         i;
    int         prev_pipe;
} t_params;

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"

// jinhyeok exec
// test driver;
unsigned char	global_signal;
void	readlilne_tester(void);

//builtin_ready.c
void	builtin_counter(t_mini *data);
int		builtin_check(t_mini *data);
void	do_builtin(t_mini *data, t_env *env);
int		only_builtin(t_mini *data, t_env *env);

//do_cd.c
void	do_cd(t_mini *data, t_env *env);
void	goto_directory(char *target, t_env *env);
void	back_directory(t_env *env);
void	home_directory(t_env *env);

//do_echo.c
void	do_echo(t_mini *data);
void	echo_write(t_mini *data, int option_idx);
int		is_echo_option(t_mini *data);

//do_env.c
void	do_env(t_env *env);

//do_exit.c
void	do_exit(t_mini *data);
int		str_digit(char *str);
void	do_exit3(int temp);
void	do_exit2(char *str);

//do_export.c
void	do_export(t_mini *data, t_env *env);
void	export_val2(t_mini *data, t_env *env);
void	set_export_env(char *key, char *value, t_env *env);
int		equal_checker(char *str);

//do_export2.c
int		is_equal(char *str);
int		export_valid_check2(char *str);
int		export_valid_check(char *key);
void	export_print(t_env *env);

//do_pwd.c
void	do_pwd(void);

//do_unset.c
void	do_unset(t_mini *data, t_env *env);
void	do_unset2(t_mini *data, int i, t_env *env);

//env_utils.c
void	ft_setenv(char *key, char *value, t_env *env);
char	*ft_getenv(char *key, t_env *env);
int		ft_envlen(t_env_node *node);
char	**env_tochar(t_env_node *env);
char	**env_tochar_join(int size, t_env_node *env);

//env_utils2.c
t_env_node	*realloc_evnode(char *key, char *value, t_env_node *node, int flag);
void		ft_nodecpy(t_env_node *new_node, t_env_node *old, char *delete);

//error.c
void	error_file(char *file);
void	error_fork(void);
void	error_pipe(void);
void	error_malloc(void);

//error2.c
void	error_cmdnotfound(char *cmd);
void	error_export_valid(char *key);
void	error_exit(char *str);
void	error_exit2(void);

//start in exec_cmd;
//void	exec_cmd(t_mini *data);
void	exec_cmd(t_mini *data, t_env *env);

//export_utils.c
char	*ft_getexport(char *key, t_env *env);
void	ft_setexport(char *key, char *value, t_env *env);

//free.c
void	command_free(char **command);
void	env_free(t_env_node *node);
void	node_free(t_mini *node);

//process_utils.c
char	**cmd_realoc(t_mini *data);
int		token_counter(t_mini *data);

//redirection_set.c
void	redirection_set(t_mini *data, t_env *env);
void	heredoc_right(t_mini *data, int i);
void	heredoc_left(t_mini *data, t_env *env, int i);
void	red_left(t_mini *data, int i);
void	red_right(t_mini *data, int i);

//process.c
void	child_execve(t_mini *data, t_env *env,int i);
void	handle_pipe_close(t_params *p, int *cur_pipe);
void	exec_fork(t_params *p, int *cur_pipe);
void	exec_cmd(t_mini *data, t_env *env);
void	parent_set(t_mini *data, int *cur_pipe, int *prev_pipe, int i);
//heredoc.c

void	file_open(t_mini *data, int i);

//redirection_util.c
void	file_create(t_mini *data, int i, int flag);
void	file_open(t_mini *data, int i);
void	set_cmd_null(t_mini *data, int start, int end);

//redirection_set.c
int		redirection_ready(t_mini *data);
void	set_redirection(t_mini *data, int i);
int		is_redirection2(char *str);

//file util
// int		is_argument(char **command, t_mini *data);

//process
void	node_free(t_mini *node);
//void	process_start2(t_mini *data);
// void	process_start2(t_mini *data, t_env *env);
//void	exec_cmd(t_mini *data);
void	cmd_find(t_mini *data, t_env *env);
void	cmd_start(t_mini *data, char **split_path, t_env *env);
char	**cmd_realoc(t_mini *data);

//free
void	command_free(char **command);
void	node_free(t_mini *node);
// t_env	*env_cpy(void);

char	*ft_getenv(char *key, t_env *env);
char	*ft_getexport(char *key, t_env *env);
void	ft_setexport(char *key,char *value, t_env *env);
void	ft_setenv(char *key, char *value, t_env *env);
char	**env_tochar(t_env_node *env);

void	goto_directory(char *target, t_env *env);
void	home_directory(t_env *env);
void	back_directory(t_env *env);
int		ft_strcmp(char *s1, char *s2);

// builtin
void	builtin_counter(t_mini *data);
int		builtin_check(t_mini *data);
void	do_builtin(t_mini *data, t_env *env);// seperate input &data[i];
int	is_dollar(char *str);

// builtin cd
void	do_cd(t_mini *data, t_env *env);
// void	do_cd2(char *to_directory, t_mini *data, t_env *env);
// int		to_back_directory(char *to_directory);
// int		to_home_directory(char *to_directory);

// builtin echo
void	echo_write(t_mini *data, int option_idx);
void	do_echo(t_mini *data);
int		is_echo_option(t_mini *data);
//void	builtin_counter2(t_mini *data);
//void	echo_option_checker(t_mini *data);

// builtin pwd
//void	do_pwd(t_mini *data, t_env *env);
void	do_env(t_env *env);
void	do_exit(t_mini *data);
void	do_exit2(char * str);
void	do_exit3(int temp);

// builtin unset
void	do_unset(t_mini *data, t_env *env);
//builtin export
void	do_export(t_mini *data, t_env *env);
void	export_sorting(t_env *env);
void	export_print(t_env *env);
void	export_val(t_mini *data, t_env *env);
void	export_val2(t_mini *data, t_env *env);
int		export_valid_check(char *key);
int		export_valid_check2(char *str);
void	set_export_env(char *key, char *value, t_env *env);

int	equal_checker(char *str);
int	is_equal(char *str);
//here_doc
// char	*set_temp_file(t_mini *data, int k);
// void	do_heredoc(t_mini *data, char **limmiter, char **temp_files);
// void	heredoc_ready(t_mini *data, t_env *env);
int		heredoc_counter(t_mini *data);
// void	temp_deleter(t_mini *data);

int			ft_envlen(t_env_node *node);
void		ft_setexport(char *key, char *value, t_env *env);
t_env_node	*realloc_evnode(char *key, char *value, t_env_node *node, int flag);
void		ft_nodecpy(t_env_node *new_node, t_env_node *old, char *delete);

//error_msg
//error.c error2.c
void	error_export_valid(char *key);
// void	error_oldpath_not_set(void);
void	error_malloc(void);
void	error_pipe(void);
void	error_fork(void);
void    error_file(char *file);
void	error_exit(char *str);
void	error_exit2(void);
void	error_execve(void);
//void	error_cmdnotfound(char *str, t_mini *data);
void	first_excute(t_mini *data, t_env *env);
int		str_digit(char *str);

//free
void	env_free(t_env_node *node);
//temp

void	heredoc_read(char *limiter, int *fd, t_env *env);
int		dollar_counter(char *str);

void	ft_wait(int n);
void	parentset(t_mini *data, int *cur_pipe, int *prev_pipe, int i);
void	childset(t_mini *data, t_env *env, int prev_pipe, int *cur_pipe);

void	dollor_conver(char *str, int *fd, t_env* env);
int	dollar_conver2(int i, t_env *env, char *str, int *fd);
int	dollar_conver3(int i, char *str, int *fd);
#endif