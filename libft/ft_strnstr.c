/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:50:34 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/07 01:52:56 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		x = 0;
		while (haystack[i + x] && needle[x] && haystack[i + x] == needle[x] && i
			+ x < n)
		{
			x++;
			if (needle[x] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
