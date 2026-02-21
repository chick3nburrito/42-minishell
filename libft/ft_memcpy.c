/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:40:21 by bamdjar           #+#    #+#             */
/*   Updated: 2024/10/27 17:24:36 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t numBytes)
{
	unsigned char	*src;
	unsigned char	*dest;
	size_t			i;

	src = (unsigned char *)from;
	dest = (unsigned char *)to;
	i = 0;
	if ((from == NULL && to == NULL) || numBytes == 0)
		return (to);
	while (i < numBytes)
	{
		dest[i] = src[i];
		i++;
	}
	return (to);
}
