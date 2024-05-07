#include "functions.h"
#include "42-libft/libft.h"
#include <sys/_types/_null.h>

static void	dollar_expend(t_main *shell)
{

}

static void	homedir_expend(t_main *shell)
{
	
}

static void	home_expend(t_main *shell)
{

}

void	expender(t_main *shell)
{
	t_expended	*exp;
	t_tokens	*t;

	t = shell->token;
	while (t != NULL)
	{
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
			dollar_expend(shell);
		else if (ft_strnstr(t->value, "~", ft_strlen(t->value)))
			home_expend(shell);
		else if (ft_strnstr(t->value, "~/", ft_strlen(t->value)))
			homedir_expend(shell);
		else
			/*oluştur ekle*/;
		t = t->next;
	}
}

// "" içinde olanlarda sadece $ değişkenleri expendlencek
// '' içinde olanlarda hiçbir değişken expendlenmeyecek
// ~ ve ~/ işaretleri expendlencek mi? expend sırasında sağı ve solu whitespace olmalı
