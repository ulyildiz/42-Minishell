NAME = minishell
SRC = initialize.c \
		main.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)

all: $(NAME)

clean:
	rm -rf *.o
	make -C 42-libft/ clean
fclean: clean
	rm -rf $(NAME)
	make -C 42-libft/ fclean
re: fclean all

.PHONY: re fclean clean all