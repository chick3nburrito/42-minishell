/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:02:42 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/07 01:38:55 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			x;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	x = 0;
	while (x < n && (s11[x] != '\0' || s22[x] != '\0'))
	{
		if (s11[x] == s22[x])
			x++;
		else
		{
			return (s11[x] - s22[x]);
		}
	}
	return (0);
}
