#include "defines.h"
#include <stdlib.h>

void	remove_quotes(t_tokens **token)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp2 = *token;
	while (tmp2 && tmp2->next)
	{
		if (tmp2->next->is_expend == NONE &&
			(tmp2->next->type == QUOTE || tmp2->next->type == D_QUOTE))
		{
			tmp = tmp2->next;
			tmp2->next = tmp->next;
			free(tmp->value);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
}

void	for_prev(t_command *cmds, t_token_types type)
{
	if (cmds->where_p == L_P && type == PIPE)
		cmds->where_p = B_P;
	else if (type == PIPE)
		cmds->where_p = R_P;
	else if (type == RDR_IN)
		cmds->where_r = R_RDR_IN;
	else if (type == RDR_OUT)
		cmds->where_r = R_RDR_OUT;
	else if (type == HEREDOC)
		cmds->where_r = R_RDR_H;
}

void	for_itself(t_command *cmds, t_token_types type)
{
	if (type == PIPE)
		cmds->where_p = L_P;
	else if (type == RDR_IN)
		cmds->where_r = L_RDR_IN;
	else if (type == RDR_OUT)
		cmds->where_r = L_RDR_OUT;
	else if (type == HEREDOC)
		cmds->where_r = L_RDR_H;
}
