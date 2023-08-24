NAME			= minishell
CC				= cc
LIB_FLAG		= -Llibft -lft
CFLAGS			= -Iinclude -g
# READLINE_FLAG	= -lreadline -L${HOME}/.brew/opt/readline/lib
# READLINE_INC	= -I${HOME}/.brew/opt/readline/include
READLINE_FLAG	= -lreadline -L/opt/homebrew/opt/readline/lib	# minjcho
READLINE_INC	= -I/opt/homebrew/opt/readline/include			# minjcho


SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include

SOURCES_NAMES	=	builtin_ready.c \
					do_cd.c \
					do_echo.c \
					do_env.c \
					do_exit.c \
					do_export.c \
					do_export2.c \
					do_pwd.c \
					do_unset.c \
					env_utils.c \
					env_utils2.c \
					error.c \
					error2.c \
					exec_cmd.c \
					export_utils.c \
					free.c \
					cmd.c \
					env_set.c \
					heredoc.c \
					parsing.c \
					parsing_utils.c \
					parsing_split_utils.c \
					parsing_put.c \
					parsing_check_utils.c \
					parsing_env.c \
					parsing_env_utils.c \
					parsing_env_utils1.c \
					process_utils.c \
					process.c \
					signal.c \
					redirection_set.c \
					redirection_util.c

SOURCES = $(addprefix $(SRC_DIR)/, $(SOURCES_NAMES))
OBJECTS = $(SOURCES_NAMES:%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJECTS)
	@make -C libft
	@$(CC) $(CFLAGS) $(LIB_FLAG) $(READLINE_FLAG) $(OBJECTS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean :
	@make clean -C libft
	@rm -f $(OBJECTS)
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(NAME) cleaned successfully."

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
