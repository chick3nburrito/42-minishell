/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:49:48 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/14 01:31:08 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i_dest;
	size_t	i_src;
	size_t	m;

	i_dest = ft_strlen(dest);
	i_src = ft_strlen(src);
	m = 0;
	if (dest == NULL || src == 0)
		return (ft_strlen(src));
	if (i_dest >= size)
		return (size + i_src);
	while (src[m] && i_dest + m < size - 1)
	{
		dest[i_dest + m] = src[m];
		m++;
	}
	dest[m + i_dest] = '\0';
	return (i_src + i_dest);
}
