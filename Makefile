NAME = minishell
SRC = initialize.c \
		main.c \
		utils.c
OBJ = $(SRC:.c=.o)
CC = cc -Wall -Wextra -Werror
LIBFT = 42-libft


$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(OBJ) $(LIBFT)/libft.a -o $(NAME)	
all: $(NAME)

clean:
	@rm -rf *.o
	@make -C $(LIBFT) clean
fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
re: fclean all

.PHONY: re fclean clean all