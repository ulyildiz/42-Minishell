#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	parent_sigint(int sig)
{
	sig = 0;
}

void	signal_reciever(int flag)
{
	if (flag == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, parent_sigint);
	}
	else if (flag == 2)
	{
		;
	}
}