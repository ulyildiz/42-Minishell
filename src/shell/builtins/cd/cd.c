
#include "functions.h"

void	cd(t_command *cmds, t_main *shell)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*cd_path;

	/* şunu farkettim bash kabuğunu ilk çağırdığımda envde old pwd yoktu
	cd ile yer değiştirdikten sonra old pwd set oldu
	bu durumu da kontrol etmeliyim
	ona göre old pwd yi set etmeliyim
	*/
	pwd = find_env(shell->envs, "PWD");
	old_pwd = find_env(shell->envs, "OLDPWD"); 
	if(!pwd)
	{
		pwd = (t_env *)malloc(sizeof(t_env));
		pwd->name = ft_strdup("PWD");
		pwd->value = getcwd(NULL, 0);
		pwd->next = NULL;
		list_add_back(&shell->envs, pwd);
	}
	if(!old_pwd)
		return(ft_putstr_fd("old pwd not set", cmds->fd[1]), ft_putstr_fd("\n", cmds->fd[1]));
	if (cmds->value[1] != NULL)
	{
		if (cmds->value[1][0] != '-')
		{
			cd_path = ft_strjoin(pwd->value, "/");
			cd_path = ft_strappend(cd_path, cmds->value[1],
					ft_strlen(cmds->value[1]));
		}
		else if (cmds->value[1][0] == '-')
		{
			cd_path = find_env(shell->envs, "OLDPWD")->value;
			ft_putstr_fd(cd_path, cmds->fd[1]);
			ft_putstr_fd("\n", cmds->fd[1]);
		}
	}
	else
		cd_path = find_env(shell->envs, "HOME")->value;
	if (chdir(cd_path) == 0)
	{
		// free(old_pwd->value);
		old_pwd->value = pwd->value;
		// free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
	else
		perror("cd");
	// free(cd_path);
	// belki "-" durumunda home a kadar sa ~ bastırabiliriz pipe a
	// freelere bakılacak
	// aklıma gelen bütün ihtimalleri denedim sıkıntı yok şuan freeleri kontrol ettikten sonra tekrar denemeliyim
}