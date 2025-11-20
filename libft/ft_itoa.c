/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:34:22 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/06 21:48:57 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	finalsize(int nb)
{
	size_t	size;
	long	nbr;

	nbr = nb;
	size = 0;
	if (nbr == 0)
		return (1);
	if (nb < 0)
		nbr = -nbr;
	while (nbr > 0)
	{
		nbr /= 10;
		size++;
	}
	return (size + (nb < 0));
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;
	long	nbr;

	size = finalsize(n);
	nbr = n;
	if (n == 0)
	{
		result = (char *)ft_calloc(sizeof(char), 2);
		result[0] = '0';
		return (result);
	}
	result = (char *)ft_calloc(sizeof(char), size + 1);
	if (!result)
		return (NULL);
	if (nbr < 0)
		nbr = nbr * (-1);
	while (size--)
	{
		result[size] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
