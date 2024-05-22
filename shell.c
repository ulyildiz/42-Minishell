#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	line_read(t_main *shell)
{
	shell->cmd_line = readline(shell->prompt);
	if (!shell->cmd_line)
		return (rl_clear_history(), perror("Readline"), 2);
	else if (!is_space(shell->cmd_line))
		return (free(shell->cmd_line), 0);
	add_history(shell->cmd_line);
	return (1);
}

void	start_shell(t_main *shell)
{
	int i;
	while(1)
	{
		i = line_read(shell);
		if (!i)
			continue ;
		else if (i == 2)
			break;
		if (!lexer(shell) && !expender(shell))
			break;
		parser(shell, shell->token, 0);
		return ;
		//executor
		//update veya free?
		shell->control = 1;
	}
}
