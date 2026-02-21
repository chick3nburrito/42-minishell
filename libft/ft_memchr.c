/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:14:38 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/12 20:22:13 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int search_str, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	c;

	s = (unsigned char *)str;
	c = (unsigned char)search_str;
	i = 0;
	while (i < n)
	{
		if (s[i] == c)
			return (s + i);
		else
			i++;
	}
	return (NULL);
}
