NAME = minishell
SRC =	src/main.c \
		src/initialize/initialize.c \
		src/utils/utils.c \
		src/free/free.c \
		src/shell/shell.c \
		src/main_structure/lexer/lexer.c \
		src/main_structure/expander/expander.c \
		src/main/utils/lexer_utils.c \
		src/main/utils/syntax_utils.c \
		src/main/utils/parser_utils.c \
		src/main/utils/expander_utils.c \
		
		

		
OBJ = $(SRC:.c=.o)
CC = cc -I ./include -I ./42-Libft # -Wall -Wextra -Werror
LIBFT = 42-libft


$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(OBJ) -lreadline $(LIBFT)/libft.a -o $(NAME) 
all: $(NAME)

clean: 
	@rm -rf *.o
	@make -C $(LIBFT) clean
fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
re: fclean all

.PHONY: re fclean clean all