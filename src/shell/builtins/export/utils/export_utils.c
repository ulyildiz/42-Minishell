/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:42:15 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/10 01:43:55 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>

extern int	add_new_env(t_env **envs, char *name, char *value);

char	*ft_exportdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (s2 == NULL)
		return ((void *)1);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	update_or_add_env_var(t_env **envs, char *name, char *value)
{
	t_env	*env_var;

	env_var = find_env(*envs, name);
	if (env_var)
	{
		if (env_var->value)
			free(env_var->value);
		env_var->value = ft_strdup(value);
		if (env_var->value == (void *)1)
			return (1);
		else
			return (0);
	}
	else
	{
		add_new_env(envs, name, value);
		return (0);
	}
}

int	handle_invalid_identifier(t_command *cmd, t_main *shell, int i)
{
	ft_putstr_fd("ft_sh: export: ", 2);
	ft_putstr_fd(cmd->value[i], 2);
	ft_putendl_fd(" : not a valid identifier", 2);
	shell->es = 1;
	return (0);
}

int	handle_assignment(t_command *cmd, t_env *envs, char *eq_pos, int i)
{
	char	*name;
	char	*value;
	int		result;

	name = ft_substr(cmd->value[i], 0, eq_pos - cmd->value[i]);
	if (!name)
		return (1);
	value = ft_exportdup(eq_pos + 1);
	if (value == (void *)1)
	{
		free(name);
		return (1);
	}
	result = update_or_add_env_var(&envs, name, value);
	free(name);
	free(value);
	return (result);
}

int	all_alphanumeric(char *str, int i)
{
	int	j;

	j = 0;
	while (str[j] && j < i)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
		j++;
	}
	return (1);
}
