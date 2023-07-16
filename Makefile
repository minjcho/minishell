NAME = minishell

CC = cc
CFLAG = -Wall -Wextra -Werror
LIB_FLAG = -Llib -lft
READLINE_FLAG =  -lreadline -L${HOME}/.brew/opt/readline/lib
INC = -I./includes/
READLINE_INC = -I${HOME}/.brew/opt/readline/include
RM = rm -f

SRC_DIR = ./srcs/
SRC =	main.c

OBJS = $(SRCS:.c=.o)
SRCS = $(addprefix $(SRC_DIR), $(SRC))

DEFAULT = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

BOLD := $(shell tput bold)
SGR0 := $(shell tput sgr0)

OPEN = $(RED)$(BOLD)\n>>
CLOSE = $(RED)$(BOLD)<<$(DEFAULT)$(SGR0)\n\n

all : $(NAME)

.c.o:
	@$(CC) $(CFLAG) $(INC) $(READLINE_INC) -c $< -o $@

$(NAME): $(OBJS)
	@make -C lib
	@$(CC) $(CFLAG) $^ $(LIB_FLAG) $(READLINE_FLAG) -o $@
	@printf "$(OPEN)$(CYAN)$(BOLD) Ready to go! $(CLOSE)"

clean :
	@make clean -C lib
	@$(RM) $(OBJS)
	@printf	"$(OPEN)$(YELLOW)$(BOLD) All cleaned $(CLOSE)"

fclean :
	@make fclean -C lib
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@printf	"$(OPEN)$(GREEN)$(BOLD) All fcleaned $(CLOSE)"

re : fclean all

.PHONY : all clean fclean re