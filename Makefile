NAME = minishell
SRC =	expender.c \
		free.c \
		initialize.c \
		lexer_utils.c \
		lexer.c \
		main.c \
		parser_utils.c \
		parser.c \
		shell.c \
		syntax_check.c \
		utils.c
OBJ = $(SRC:.c=.o)
CC = cc -Wall -Wextra -Werror
LIBFT = 42-libft


$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(OBJ) -lreadline $(LIBFT)/libft.a -o $(NAME)
all: $(NAME)

clean: 
	@rm -rf *.o
	@make -C $(LIBFT) clean
fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
re: fclean all

.PHONY: re fclean clean all