# NAME = minishell

# CC = cc
# CFLAG = -Wall -Wextra -Werror
# LIB_FLAG = -Llib -lft
# READLINE_FLAG =  -lreadline -L${HOME}/.brew/opt/readline/lib
# INC = -I./includes/
# READLINE_INC = -I${HOME}/.brew/opt/readline/include
# RM = rm -f

# SRC_DIR = ./srcs/
# SRC =	main.c

# OBJS = $(SRCS:.c=.o)
# SRCS = $(addprefix $(SRC_DIR), $(SRC))

# DEFAULT = \033[0m
# BLACK = \033[0;30m
# RED = \033[0;31m
# GREEN = \033[0;32m
# YELLOW = \033[0;33m
# BLUE = \033[0;34m
# PURPLE = \033[0;35m
# CYAN = \033[0;36m
# WHITE = \033[0;37m

# BOLD := $(shell tput bold)
# SGR0 := $(shell tput sgr0)

# OPEN = $(RED)$(BOLD)\n>>
# CLOSE = $(RED)$(BOLD)<<$(DEFAULT)$(SGR0)\n\n

# all : $(NAME)

# .c.o:
# 	@$(CC) $(CFLAG) $(INC) $(READLINE_INC) -c $< -o $@

# $(NAME): $(OBJS)
# 	@make -C lib
# 	@$(CC) $(CFLAG) $^ $(LIB_FLAG) $(READLINE_FLAG) -o $@
# 	@printf "$(OPEN)$(CYAN)$(BOLD) Ready to go! $(CLOSE)"

# clean :
# 	@make clean -C lib
# 	@$(RM) $(OBJS)
# 	@printf	"$(OPEN)$(YELLOW)$(BOLD) All cleaned $(CLOSE)"

# fclean :
# 	@make fclean -C lib
# 	@$(RM) $(OBJS)
# 	@$(RM) $(NAME)
# 	@printf	"$(OPEN)$(GREEN)$(BOLD) All fcleaned $(CLOSE)"

# re : fclean all

# .PHONY : all clean fclean re

NAME			= minishell
CC				= cc
LIB_FLAG		= -Llibft -lft
CFLAGS			= -Iinclude -g -Wall -Wextra -Werror  #추가 해야함
READLINE_FLAG	=  -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC	= -I${HOME}/.brew/opt/readline/include
# READLINE_FLAG	= -lreadline -L/opt/homebrew/opt/readline/lib	# minjcho
# READLINE_INC	= -I/opt/homebrew/opt/readline/include			# minjcho


SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include

SOURCES_NAMES	=	builtin_ready.c \
					do_cd.c \
					do_echo.c \
					do_env.c \
					do_exit.c \
					do_export.c \
					do_pwd.c \
					do_unset.c \
					env_utils.c \
					env_utils2.c \
					error.c \
					error2.c \
					exec_cmd.c \
					export_utils.c \
					free.c \
					here_doc2.c \
					heredoc.c \
					process_utils.c \
					process.c \
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
