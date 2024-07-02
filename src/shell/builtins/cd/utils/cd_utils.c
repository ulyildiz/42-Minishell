#include "functions.h"

t_env *create_env(char *name, char *value)
{
    t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
    if (!env)
		return (NULL);
    env->name = ft_strdup(name);
    if (!env->name)
		return (free(env), NULL);
    if (value)
	{
        env->value = ft_strdup(value);
        if (!env->value)
			return (free(env->name), free(env), NULL);
    }
	else
        env->value = "\0";
    env->next = NULL;
    return env;
}

int set_env_value(t_env *env, char *value)
{
    if (env->value)
        free(env->value);
    if (value)
	{
        env->value = ft_strdup(value);
        if (!env->value)
            return -1;
    }
	else
        env->value = "\0";
    return 0;
}

t_env *update_or_create_env(t_env **envs, char *name, char *value)
{
    t_env *env;

	env = find_env(*envs, name);
    printf("env: %s\n envs:%s\n", env->name,env->value);
    if (!env || !env->value)
	{
        env = create_env(name, value);
        if (!env)
			return NULL;
        list_add_back(envs, env);
    }
	else if (env && env->value)
	{
        if (set_env_value(env, value) != 0)
			return (NULL);
	}
    return (env);
}

char *append_path(char *base, char *append)
{
    char *path;
	char *tmp;

	path  = ft_strjoin(base, "/");
    if (!path)
		return (NULL);
	tmp = ft_strappend(path, append, ft_strlen(append));
    if (!tmp)
		return (free(path), NULL);
    return (tmp);
}
