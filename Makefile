NAME = minishell
SRC =   src/main.c \
        src/initialize/initialize.c \
        src/shell/shell.c \
        src/shell/signal/signal.c \
        src/utils/free/free.c \
        src/shell/main_structure/lexer/lexer.c \
        src/shell/main_structure/lexer/utils/lexer_utils.c \
        src/shell/main_structure/lexer/utils/lexer_utils2.c \
        src/shell/main_structure/expander/expander.c \
        src/shell/main_structure/expander/utils/expander_utils.c \
		src/shell/main_structure/expander/utils/expander_utils2.c \
		src/shell/main_structure/expander/utils/expander_utils3.c \
        src/shell/main_structure/parser/parser.c \
        src/shell/main_structure/parser/utils/parser_utils.c \
        src/shell/main_structure/parser/utils/parser_utils2.c \
        src/shell/main_structure/parser/utils/parser_utils3.c \
        src/shell/main_structure/executer/executer.c \
        src/shell/main_structure/executer/utils/executer_utils.c \
        src/shell/main_structure/executer/utils/executer_utils2.c \
		src/shell/main_structure/executer/utils/executer_utils3.c \
		src/shell/main_structure/executer/utils/heredoc.c \
        src/utils/exits.c \
        src/utils/utils.c \
        src/utils/syntax_check.c \
        src/shell/builtins/utils/builtins_utils.c \
        src/shell/builtins/utils/builtins_utils2.c \
        src/shell/builtins/echo/echo.c \
        src/shell/builtins/cd/cd.c \
        src/shell/builtins/cd/utils/cd_utils.c \
        src/shell/builtins/pwd/pwd.c \
        src/shell/builtins/export/export.c \
        src/shell/builtins/export/utils/export_utils.c \
        src/shell/builtins/unset/unset.c \
        src/shell/builtins/env/env.c \
        src/shell/builtins/exit/exit.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -I ./include -I ./42-Libft -Wall -Wextra -Werror
LIBFT = 42-libft
LIBFT_A = $(LIBFT)/libft.a

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(OBJ) -lreadline $(LIBFT_A) -o $(NAME)
	@echo "\033[0;32mProgram $(NAME) başarılayla derlendi.\033[0m"

$(OBJ_DIR)/%.o: %.c $(deps)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT) clean
	@echo "\033[0;32mObje dosyaları temizlendi.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
	@echo "\033[0;32mTüm derleme dosyaları temizlendi.\033[0m"

re: fclean all

.PHONY: re fclean clean all 
