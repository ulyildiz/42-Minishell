/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:59:01 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/10 23:00:51 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *bigger)
{
	int	i;

	i = 0;
	if (!bigger)
		return (NULL);
	while (bigger[i])
	{
		bigger[i] = ft_tolower(bigger[i]);
		i++;
	}
	return (bigger);
}
