
#include "functions.h"

void	deleteNode(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	if (temp != NULL && ft_strncmp(temp->name, key, ft_strlen(temp->name)) == 0)
	{
		*head = temp->next;
		return (free(temp));
	}
	while (temp != NULL && ft_strncmp(temp->name, key,
			ft_strlen(temp->name)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
}

void	unset(t_command *cmds, t_main *shell)
{
	int i;

	i = 1;
	while (cmds->value[i] != NULL)
	{
		deleteNode(&shell->envs, cmds->value[i]);
		i++;
	}
	//d0nE
}
