#include "functions.h"
#include "42-libft/libft.h"
#include <sys/_types/_null.h>

static void	dollar_expend(t_main *shell)
{

}

static void	homedir_expend(t_tokens *token)
{
	char	*expnd_value;

	if (token->is_expend != NONE)
		return ;
	expnd_value = find_env();
}

void	expender(t_main *shell)
{
	t_tokens	*t;

	t = shell->token;
	while (t != NULL)
	{
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
			dollar_expend(t);
		else if (ft_strnstr(t->value, "~", ft_strlen(t->value))
			|| ft_strnstr(t->value, "~/", ft_strlen(t->value)))
			homedir_expend(t);
		t = t->next;
	}
}

// "" içinde olanlarda sadece $ değişkenleri expendlencek
// '' içinde olanlarda hiçbir değişken expendlenmeyecek
// ~ ve ~/ işaretleri expendlencek mi? expend sırasında sağı ve solu whitespace olmalı
