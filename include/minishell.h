/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:14:11 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:07:33 by jinhyeok         ###   ########.fr       */
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
	char		**file_container;
} t_env;

typedef struct s_mini
{
	char	**command;
	char	**temp_files;
	int		doc_cnt;
	int		cmd_size;
	int		delete;
	int		output_fd;
	int		input_fd;
	int		origin_in;
	int		origin_out;
	int		cnt;
	int		builtin_cnt;
} t_mini; 

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"

// jinhyeok exec
// test driver;
void	readlilne_tester(void);

//start in exec_cmd;
//void	exec_cmd(t_mini *data);
void	exec_cmd(t_mini *data, t_env *env);
void	file_open(t_mini *data, int i);
void	error_file(void);

//redirection_util.c
void	file_create(t_mini *data, int i, int flag);
void	file_open(t_mini *data, int i);
void	set_cmd_null(t_mini *data, int start, int end);

//redirection_set.c
int		redirection_ready(t_mini *data);
void	set_redirection(t_mini *data, int i);
int		is_redirection(char *str);

//file util
int		is_argument(char **command, t_mini *data);

//process
void	node_free(t_mini *node);
//void	process_start2(t_mini *data);
void	process_start2(t_mini *data, t_env *env);
//void	exec_cmd(t_mini *data);
void	cmd_find(t_mini *data, t_env *env);
void	cmd_start(t_mini *data, char **split_path, t_env *env);
char	**cmd_realoc(t_mini *data);

//free
void	command_free(char **command);
void	node_free(t_mini *node);
t_env	*env_cpy(void);

char	*ft_getenv(char *key, t_env *env);
char	*ft_getexport(char *key, t_env *env);
void	ft_setexport(char *key,char *value, t_env *env);
void	ft_setenv(char *key, char *value, t_env *env);
char	**env_tochar(t_env_node *env);
void	error_path_not_set(char *path_name);

void	goto_directory(char *target, t_env *env);
void	home_directory(t_env *env);
void	back_directory(t_env *env);
int		ft_strcmp(char *s1, char *s2);

// builtin
void	builtin_counter(t_mini *data);
int		builtin_check(t_mini *data);
void	do_builtin(t_mini *data, t_env *env);// seperate input &data[i];

// builtin cd
void	do_cd(t_mini *data, t_env *env);
void	do_cd2(char *to_directory, t_mini *data, t_env *env);
int		to_back_directory(char *to_directory);
int		to_home_directory(char *to_directory);

// builtin echo
void	do_echo(t_mini *data);
int		is_echo_option(t_mini *data);
//void	echo_option_checker(t_mini *data);

// builtin pwd
void	do_pwd(t_mini *data, t_env *env);
void	do_env(t_env *env);
void	do_exit(t_mini *data);

// builtin unset
void	do_unset(t_mini *data, t_env *env);
//builtin export
void	do_export(t_mini *data, t_env *env);
void	export_sorting(t_env *env);
void	export_print(t_env *env);
void	export_val(t_mini *data, t_env *env);
int		export_valid_check(char *key);

//here_doc
char	*set_temp_file(t_mini *data, int k);
void	do_heredoc(t_mini *data, char **limmiter, char **temp_files);
void	heredoc_ready(t_mini *data, t_env *env);
int		heredoc_counter(t_mini *data);
void	temp_deleter(t_mini *data);

int			ft_envlen(t_env_node *node);
void		ft_setexport(char *key, char *value, t_env *env);
t_env_node	*realloc_evnode(char *key, char *value, t_env_node *node, int flag);
void		ft_nodecpy(t_env_node *new_node, t_env_node *old, char *delete);

//error_msg
//error.c error2.c
void	error_export_valid(char *key);
void	error_oldpath_not_set(void);
void	error_malloc(void);
void	error_pipe(void);
void	error_fork(void);
void    error_file(void);
void	error_execve(void);
void	error_cmdnotfound(char *str, t_mini *data);
void	first_excute(t_mini *data, t_env *env);

//free
void	env_free(t_env_node *node);

#endif