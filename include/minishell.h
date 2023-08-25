/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:14:11 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/25 17:52:12 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_env_node
{
	char	*key;
	char	*value;
}	t_env_node;

typedef struct s_env
{
	t_env_node	*node;
	t_env_node	*export;
}	t_env;

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
	int		is_signal;
	int		echo_fail;
}	t_mini;

typedef struct s_params
{
	t_mini		*data;
	t_env		*env;
	int			i;
	int			prev_pipe;
}	t_params;

typedef struct s_state
{
	char	**result;
	int		idx;
	size_t	i;
	size_t	start;
	char	quote;
}	t_state;

unsigned char	g_signal;
void			readlilne_tester(char **envp);
//builtin_ready.c
void			builtin_counter(t_mini *data);
int				builtin_check(t_mini *data);
void			do_builtin(t_mini *data, t_env *env);
int				only_builtin(t_mini *data, t_env *env);
//do_cd.c
void			do_cd(t_mini *data, t_env *env);
void			goto_directory(char *target, t_env *env);
void			back_directory(t_env *env);
void			home_directory(t_env *env);
//do_echo.c
void			echo_write(t_mini *data, int option_idx);
int				is_echo_option(t_mini *data);
//do_env.c
void			do_env(t_env *env);
//do_exit.c
void			do_exit(t_mini *data);
int				str_digit(char *str);
void			do_exit3(int temp, int cnt);
void			do_exit2(char *str);
//do_export.c
void			do_export(t_mini *data, t_env *env);
void			export_val2(t_mini *data, t_env *env);
void			set_export_env(char *key, char *value, t_env *env);
int				equal_checker(char *str);
//do_export2.c
int				is_equal(char *str);
int				export_valid_check2(char *str);
int				export_valid_check(char *key);
void			export_print(t_env *env);
//do_pwd.c
void			do_pwd(void);
//do_unset.c
void			do_unset(t_mini *data, t_env *env);
void			do_unset2(t_mini *data, int i, t_env *env);
//env_utils.c
void			ft_setenv(char *key, char *value, t_env *env);
char			*ft_getenv(char *key, t_env *env);
int				ft_envlen(t_env_node *node);
char			**env_tochar(t_env_node *env);
char			**env_tochar_join(int size, t_env_node *env);
//env_utils2.c
t_env_node		*realloc_evnode(char *key, char *value, \
									t_env_node *node, int flag);
void			ft_nodecpy(t_env_node *new_node, t_env_node *old, char *delete);
//error.c
void			error_file(char *file);
void			error_fork(void);
void			error_pipe(void);
void			error_malloc(void);
//error2.c
void			error_cmdnotfound(char *cmd);
void			error_export_valid(char *key);
void			error_exit(char *str);
void			error_exit2(void);
//start in exec_cmd;
void			exec_cmd(t_mini *data, t_env *env);
//export_utils.c
char			*ft_getexport(char *key, t_env *env);
void			ft_setexport(char *key, char *value, t_env *env);
//free.c
void			command_free(char **command);
void			env_free(t_env_node *node);
void			node_free(t_mini *node);
//process_utils.c
char			**cmd_realoc(t_mini *data);
int				token_counter(t_mini *data);
int				is_redirection2(char *str);
void			ft_wait(int n);
void			origin_dup(t_mini *data, int i);
//redirectioxn_set.c
void			redirection_set(t_mini *data, t_env *env);
void			heredoc_right(t_mini *data, int i);
void			heredoc_left(t_mini *data, t_env *env, int i);
void			red_left(t_mini *data, int i);
void			red_right(t_mini *data, int i);
//process.c
void			child_execve(t_mini *data, t_env *env, int i);
void			handle_pipe_close(t_params *p, int *cur_pipe);
void			exec_fork(t_params *p, int *cur_pipe);
void			parent_set(t_mini *data, int *cur_pipe, int *prev_pipe, int i);
void			control_pipe(int *cur_pipe);
int				set_re_and_pipe(t_mini *data, t_env *env, int *cur_pipe, int i);
//redirection_util.c
int				ft_strcmp(char *s1, char *s2);
void			set_cmd_null(t_mini *data, int start, int end);
//cmd.c
void			first_excute(t_mini *data, t_env *env);
void			cmd_find(t_mini *data, t_env *env);
void			cmd_start(t_mini *data, char **split_path, t_env *env);
int				is_slash(char *str);
//free
void			command_free2(char **command, int size);
void			node_free2(t_mini *node);
// builtin echo
void			do_echo(t_mini *data);
void			export_sorting(t_env *env);
//error.c error2.c
void			error_cmd2(char *cmd, int i);
//heredoc.c
int				dollar_counter(char *str);
void			heredoc_read(char *limiter, int *fd, t_env *env);
void			dollor_conver(char *str, int *fd, t_env *env);
int				dollar_conver2(int i, t_env *env, char *str, int *fd);
int				dollar_conver3(int i, char *str, int *fd);
//env_set.c
void			env_init(t_env *env, char **envp);
void			envp_split(t_env *env, char **envp);
int				envp_size(char **envp);
void			env_substr(t_env *env, char **envp, int i, int j);
//signal
void			sigint_handler(int signal);
void			signal_main(void);
void			signal_heredoc(t_mini *data, int status);
void			heredoc_signal_red(pid_t id, int *fd, t_mini *data);
//minjcho
bool			parsing(t_mini **mini, char *line);
bool			check_struct(t_mini	*mini, t_env *env);
void			ft_strncpy(char *dest, char *src, int n);
void			ft_strcpy(char *dest, char *src);
void			ft_strcat(char *dest, char *src);
char			*ft_strstr(char *str, char *to_find);
int				count_pipes(char **tmp_command);
void			allocate_and_set_command(t_mini *mini, char **tmp_command, \
									int cmd_count, int start_idx);
void			update_indices_and_count(int *cmd_count, int *cmd_idx, \
									int *start_idx, int i);
void			put_struct(t_mini **mini, char **tmp_command);
bool			check_and_print_error(char *current, char *next);
bool			consecutive_redirection(t_mini *mini);
bool			check_empty_redirection(t_mini *mini);
bool			has_invalid_redirection(char *token);
bool			check_redirection(t_mini *mini);
char			**split_string(char *input);
void			env_replace(char **str, char *tmp, t_env *env, \
								bool in_double_quote);
char			*find_env_variable(char *str);
bool			replace_env_in_double_quote(char **str, t_env *env);
void			put_g_signal(char **str, int start_idx);
void			replace_env(t_mini *mini, t_env *env);
char			is_special_t(char c);
int				is_alpha_num(char c);

#endif