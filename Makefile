NAME			= minishell
CC				= cc
LIB_FLAG		= -Llibft -lft
CFLAGS			= -Iinclude #-Wall -Wextra -Werror 추가 해야함
READLINE_FLAG	= -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC	= -I${HOME}/.brew/opt/readline/include
# READLINE_FLAG	= -lreadline -L/opt/homebrew/opt/readline/lib	# minjcho
# READLINE_INC	= -I/opt/homebrew/opt/readline/include			# minjcho


SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include

SOURCES_NAMES	=	main.c \
					parsing.c \
					readline_check.c \
					ft_split2.c \

SOURCES = $(addprefix $(SRC_DIR)/, $(SOURCES_NAMES))
OBJECTS = $(SOURCES_NAMES:%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJECTS)
	@make -C libft
	@$(CC) $(CFLAGS) $(LIBLIBS) $(READLINE_FLAG) $(OBJECTS) -o $(NAME)

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
