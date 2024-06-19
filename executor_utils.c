#include "42-libft/libft.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	accessibility(t_command *cmds, t_main *shell)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (access(cmds->value[0], X_OK) != 0)
	{
		tmp = ft_strjoin("/", cmds->value[0]);
		if (!tmp)
			return (perror("Access"), 0);
		while (shell->paths[i])
		{
			cmds->cmd_and_path = ft_strjoin(shell->paths[i], tmp);
			if (access(cmds->cmd_and_path, X_OK) == 0)
				return (free(tmp), 1);
			free(cmds->cmd_and_path);
			i++;
		}
		free(tmp);
	}
	else
	{
		cmds->cmd_and_path = ft_strdup(cmds->value[0]);
		return (1);
	}
	return (0);
}

void	close_fd(t_command *cmds, int flag)
{
	if (!cmds)
		return ;
}

void	echo(t_command *cmds, t_main *shell)
{
	size_t	i;
	size_t	j;
	int		newline;

	i = 1;
	newline = 1;
	if (cmds->value[i] && cmds->value[i][0] == '-')
	{
		while (cmds->value[i] && cmds->value[i][0] == '-')
		{
			j = 1;
			while (cmds->value[i][j] == 'n')
				j++;
			if (cmds->value[i][j] == '\0')
				newline = 0;
			else
				break ;
			i++;
		}
	}
	if (cmds->value[i])
		ft_putstr_fd(cmds->value[i++], cmds->fd[1]);
	while (cmds->value[i])
	{
		ft_putstr_fd(" ", cmds->fd[1]);
		ft_putstr_fd(cmds->value[i++], cmds->fd[1]);
	}
	if (newline)
		ft_putstr_fd("\n", cmds->fd[1]);
}

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
	pwd = find_env(shell->envs, "PWD");        // kontrol et not set olabilir
	old_pwd = find_env(shell->envs, "OLDPWD"); // kontrol et not set olabilir
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

void	pwd(t_command *cmds, t_main *shell)
{
	t_env	*pwd;

	pwd = find_env(shell->envs, "PWD");
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd->value, cmds->fd[1]);
		ft_putstr_fd("\n", cmds->fd[1]);
		// normal bash ile karşılaştırdım newline atıyor rdr de bile
	} // olmama durumunu kontrol etmelisin
}

void	env(t_command *cmds, t_main *shell)
{
	t_env	*env;

	env = shell->envs;
	while (env != NULL)
	{
		if (env->name != 0)
		{
			ft_putstr_fd(env->name, cmds->fd[1]);
			ft_putstr_fd("=", cmds->fd[1]);
		}
		if (env->value != NULL)
			ft_putstr_fd(env->value, cmds->fd[1]);
		ft_putstr_fd("\n", cmds->fd[1]);
		// eğer value ya sahip olmayan nameler varsa = den sonra direkt newline atmıyordu ondan if dışında
		env = env->next;
	}
}

void	deleteNode(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	// Silinecek düğümün baş düğüm olup olmadığını kontrol et
	if (temp != NULL && ft_strncmp(temp->name, key, ft_strlen(temp->name)) == 0)
	{
		*head = temp->next; // Baş düğümü değiştir
		free(temp);         // Eski baş düğümü serbest bırak
		return ;
	}
	// Silinecek düğümü bulana kadar listede gez
	while (temp != NULL && ft_strncmp(temp->name, key,
			ft_strlen(temp->name)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	// Eğer düğüm bulunamadıysa
	if (temp == NULL)
		return ;
	// Düğümü listeden çıkar
	prev->next = temp->next;
	free(temp); // Belleği serbest bırak
}

void	unset(t_command *cmds, t_main *shell)
{
	deleteNode(&shell->envs, cmds->value[1]);
}

static t_env	*sort_export(t_env *lst, int (*cmp)(int, int))
{
	char	*swap_name;
	char	*swap_value;
	t_env	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->name[0], lst->next->name[0])) == 0)
		{
			swap_name = lst->name;
			swap_value = lst->value;
			lst->name = lst->next->name;
			lst->value = lst->next->value;
			lst->next->name = swap_name;
			lst->next->value = swap_value;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
int	ascending(int a, int b)
{
	return (a <= b);
}
void	export(t_command *cmds, t_main *shell)
{
	t_env	*export;
	t_env	*copy;
	t_env	*tmp;
	int		i;
	char	**str;

	i = 1;
	while (cmds->value[i])
	{
		str = ft_split(cmds->value[i], '=');
		if (str[0] && find_env(shell->envs, str[0]) != NULL)
		{
			if (str[1])
				find_env(shell->envs, str[0])->value = str[1];
		}
		else if (str[0] && find_env(shell->envs, str[0]) == NULL)
		{
			tmp = (t_env *)malloc(sizeof(t_env));
			if (!tmp)
				return ;
			tmp->name = str[0];
			tmp->value = "\0";
			tmp->next = NULL;
			if (str[1])
			{
				tmp->value = ft_strjoin("\"", str[1]);
				tmp->value = ft_strappend(tmp->value, "\"", 1);
			}
			list_add_back(&(shell->envs), tmp);
		}
		i++;
	}
	copy = shell->envs;
	export = NULL;
	while (copy)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (free_env(export));
		tmp->name = ft_strdup(copy->name);
		if (!tmp->name)
			return (free(tmp), free_env(export));
		tmp->value = ft_strdup(copy->value);
		if (!tmp->value)
			return (free(tmp->name), free(tmp), free_env(export));
		tmp->next = NULL;
		list_add_back(&export, tmp);
		copy = copy->next;
	}
	export = sort_export(export, ascending);
	while (export)
	{
		ft_putstr_fd("declare -x ", cmds->fd[1]);
		ft_putstr_fd(export->name, cmds->fd[1]);
		if (export->value != NULL && export->value[0] != '\0')
		{
			ft_putstr_fd("=", cmds->fd[1]);
			ft_putstr_fd("\"", cmds->fd[1]);
			ft_putstr_fd(export->value, cmds->fd[1]);
			ft_putstr_fd("\"", cmds->fd[1]);
		}
		ft_putstr_fd("\n", cmds->fd[1]);
		export = export->next;
	}
}

void	exit_cmd(t_command *cmds, t_main *shell)
{
	ft_putstr_fd("exit", cmds->fd[1]);
	ft_putstr_fd("\n", cmds->fd[1]);
	/*
	free işlemleri yapılacak
	ama bu kısmı projenin sonuna bırakıyorum
	*/
	exit(0);
}

int	is_builtin(t_command *cmds, t_main *shell)
{
	int				i;
	static t_build	commands[] = {{"echo", echo}, {"cd", cd}, {"pwd", pwd},
			{"env", env}, {"unset", unset}, {"export", export}, {"exit",
			exit_cmd}, {NULL, NULL}};

	i = 0;
	while (commands[i].name)
	{
		if (ft_strncmp(ft_strlower(cmds->value[0]), commands[i].name,
				ft_strlen(cmds->value[0])) == 0)
		{
			commands[i].func(cmds, shell);
			return (1);
		}
		i++;
	}
	return (0);
}
