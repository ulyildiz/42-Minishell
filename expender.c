#include "functions.h"
#include "42-libft/libft.h"
#include <sys/_types/_null.h>
#include <stdio.h>
#include <unistd.h>

static int	dollar_expend(t_tokens *token, t_env *env)
{
	t_env	*expnd_value;
	size_t i;
	size_t j;
	char	*tmp;
	if (token->is_expend == WITHIN_Q)
		return (1);
	i = 0;
	tmp = ft_strdup("");
	expnd_value = env;
	char *deneme;
	deneme = ft_strdup("");
	while (token->value[i])
	{
		if(token->value[i] == '$' && token->value[i + 1] == '$')
		{
			tmp = ft_strappend(tmp,ft_itoa(getpid()),ft_strlen(ft_itoa(getpid())));
			i++;
		}
		else if(token->value[i] == '$' && token->value[i + 1] == '?')
		{
			tmp = ft_strappend(tmp, "0", 1);
			i++;
		}
		else if (token->value[i] == '$' && token->value[i + 1] == '\0')
		{
			tmp = ft_strappend(tmp,"$",1);
			i++;
		}
		else if (token->value[i] == '$' && ft_isalnum(token->value[i + 1]) == 1)
		{
			i++;
			j = 0;
			while (ft_isalnum(token->value[i + j]))
				j++;
			deneme = (char *)ft_memcpy(deneme,&token->value[i],j);
			deneme[i + j] = '\0';
			expnd_value = find_env(env,deneme);
			if (expnd_value)
			{
				tmp = ft_strappend(tmp,expnd_value->value,ft_strlen(expnd_value->value));
			}
			free(deneme);
		}
		i++;
	}
	free(token->value);
	token->value = ft_strdup("");
	token->value = ft_strappend(token->value,tmp,ft_strlen(tmp));
	//printf("%s\n",token->value);
	return(1);
}

static int	homedir_expend(t_tokens *token, t_env *env)
{
	t_env	*expnd_value;
	char	*tmp;

	if (token->is_expend != NONE)
		return (1);
	expnd_value = find_env(env, "HOME");//find envye envin olmama durumunu ekle
	if (!expnd_value)
		return (/*whle(1) döngüsüne çıkart*/ 0);
	tmp = token->value;
	token->value = ft_strjoin(expnd_value->value, token->value + 1);
	free(tmp);
	if(!token->value)
		return(/*malloc hatası*/0);
	return (1);
}

static int	home_expend(t_tokens *token, t_env *env)
{
	t_env	*expnd_value;

	if (token->is_expend != NONE)
		return (1);
	expnd_value = find_env(env, "HOME");
	if (!expnd_value)
		return (0);
	free(token->value);
	token->value = ft_strdup(expnd_value->value);
	if (!token->value)
		return (/*malloc hatası*/ 0);
	return (1);
}

void	expender(t_main *shell)
{
	t_tokens	*t;

	if (shell->control == 0)
		return ;
	t = shell->token;
	while (t != NULL)
	{
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
		{
			if (!dollar_expend(t, shell->envs))
				return ;
		}
		else if (ft_strnstr(t->value, "~/", ft_strlen(t->value)))
		{
			if (!homedir_expend(t, shell->envs))
				return ;
		}
		else if (ft_strnstr(t->value, "~", ft_strlen(t->value)))
		{
			if (!home_expend(t, shell->envs))
				return ;
		}
		//printf("%s\n",t->value);
		t = t->next;
	}
}

// "" içinde olanlarda sadece $ değişkenleri expendlencek
// '' içinde olanlarda hiçbir değişken expendlenmeyecek
// ~ ve ~/ işaretleri expendlencek mi? expend sırasında sağı ve solu whitespace olmalı
