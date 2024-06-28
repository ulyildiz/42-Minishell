
#include "functions.h"

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
	int i;

	i = 1;
	while (cmds->value[i] != NULL)
	{
		deleteNode(&shell->envs, cmds->value[i]);
		i++;
	}
	//d0nE
}