#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>

int	accessibility(t_command *cmds, t_main *shell)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin("/",cmds->value[0]); // tmp kontrol et
/* 	if (!tmp)
		return (perror("Access"), ); */
	while (shell->paths[i])
	{	
		cmds->cmd_and_path = ft_strjoin(shell->paths[i],tmp);
		if (access(cmds->cmd_and_path, X_OK) == 0)
			return(free(tmp), 1);
		free(cmds->cmd_and_path);
		i++;
	}
	free(tmp);
	return (0);
}

void	close_fd(t_command *cmds, int flag)
{
	if (!cmds)
		return ;

}

void echo(t_command *cmds, t_main *shell) {
    printf("echo command\n");
}

void cd(t_command *cmds, t_main *shell) {
    printf("cd command\n");
}

void pwd(t_command *cmds, t_main *shell) {
    printf("pwd command\n");
}

void env(t_command *cmds, t_main *shell) {
    printf("env command\n");
}

void unset(t_command *cmds, t_main *shell) {
    printf("unset command\n");
}

void export(t_command *cmds, t_main *shell) {
    printf("export command\n");
}

void exit_cmd(t_command *cmds, t_main *shell) {
    printf("exit command\n");
    exit(0);
}

int	is_builtin(t_command *cmds, t_main *shell)
{
	int				i;
	static t_build	commands[] = {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"env", env},
	{"unset", unset},
	{"export", export},
	{"exit", exit_cmd},
	{NULL, NULL}
	};

	i = 0;
	while (commands[i].name)
	{
		if (ft_strncmp(cmds->value[0], commands[i].name, ft_strlen(cmds->value[0])) == 0) 
		{
            commands[i].func(cmds, shell);
            return (1);
		}
		i++;
	}
	return (0);
}
