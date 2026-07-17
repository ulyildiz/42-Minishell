/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:02:24 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/26 12:28:38 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupper(char *lower)
{
	int	i;

	i = 0;
	while (lower[i])
	{
		lower[i] = ft_toupper(lower[i]);
		i++;
	}
	return (lower);
}
