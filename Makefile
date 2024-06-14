NAME = minishell
SRC =	src/main.c \
		src/initialize/initialize.c \
		src/utils/utils.c \
		src/free/free.c \
		src/shell/shell.c \
		src/main_structure/lexer/lexer.c
		
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