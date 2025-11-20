/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:45:08 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/07 00:44:07 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)str;
	while (i < n)
	{
		ptr[i] = value;
		i++;
	}
	return (ptr);
}
