#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	prompt(t_main *shell) // user + : + pwd + ->
{
	char	*tmp;

	shell->prompt = ft_strdup(find_env(shell->envs, "LOGNAME")->value); //LOGNAME standart bir env mi?
	if (!shell->prompt)
		return ;
	tmp = ft_strjoin(shell->prompt, ":");
	if (!tmp)
		return /*mesaj free*/;
	free(shell->prompt);
	shell->prompt = tmp;
	tmp = ft_strjoin(shell->prompt, getcwd(NULL, 0));// yada direkt envden çekmek?
	if (!tmp)
		return /*mesaj free*/;
	free(shell->prompt);
	shell->prompt = tmp;
	tmp = ft_strjoin(shell->prompt, "->");
	if (!tmp)
		return /*mesaj free*/;
	free(shell->prompt);
	shell->prompt = tmp;
}

static int	line_read(t_main *shell)
{
	prompt(shell);
	shell->cmd_line = readline(shell->prompt);
	if (!shell->cmd_line)
	{
		rl_clear_history();
	//	free_env(shell);
		/*freele programı kapat programı kapat*/
		exit(1);
	}
	else if (!is_space(shell->cmd_line))
		return (free(shell->cmd_line), free(shell->prompt), 0);
	add_history(shell->cmd_line);
	return (1);
}

void	start_shell(t_main *shell)
{
	while(1)
	{
		if (!line_read(shell))
			continue ;
		//lexer
		//expender
		//parser
		//executor
		//update veya free?
	}
}
