/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:50:47 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/11 14:50:47 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *s1, char *s2, size_t len)
{
	char *s3;
	int i;
	int j;

	j = len;
	i = ft_strlen(s1);
	s3 = (char *)malloc(i + j + 1);
	if (s3 == NULL)
		return (free(s1), NULL); //double free var mı bak
	ft_memcpy(s3, s1, i);
	ft_memcpy(s3 + i, s2, j);
	s3[i + j] = '\0';
	free(s1);
	return (s3);
}