NAME = minishell
SRC =	src/main.c \
		src/initialize/initialize.c \
		src/shell/shell.c \
		src/shell/signal.c \
		src/utils/free/free.c \
		src/shell/main_structure/lexer/lexer.c \
		src/shell/main_structure/lexer/utils/lexer_utils.c \
		src/shell/main_structure/lexer/utils/lexer_utils2.c \
		src/shell/main_structure/expander/expander.c \
		src/shell/main_structure/expander/utils/expander_utils.c \
		src/shell/main_structure/parser/parser.c \
		src/shell/main_structure/parser/utils/parser_utils.c \
		src/shell/main_structure/executer/executer.c \
		src/shell/main_structure/executer/utils/executer_utils.c \
		src/utils/utils.c \
		src/utils/syntax_check.c \
		src/shell/builtins/utils/builtins_utils.c \
		src/shell/builtins/echo/echo.c \
		src/shell/builtins/cd/cd.c \
		src/shell/builtins/pwd/pwd.c \
		src/shell/builtins/export/export.c \
		src/shell/builtins/unset/unset.c \
		src/shell/builtins/env/env.c \
		src/shell/builtins/exit/exit.c \

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -I ./include -I ./42-Libft -Wall -Wextra -Werror
LIBFT = 42-libft
LIBFT_A = $(LIBFT)/libft.a

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(OBJ) -lreadline $(LIBFT_A) -o $(NAME) 

all: $(NAME)

clean: 
	@rm -rf $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: re fclean clean all
