/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:26:16 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/07 02:38:38 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	sign;
	int	result;

	index = 0;
	sign = 1;
	result = 0;
	while ((str[index] >= 9 && str[index] <= 13) || (str[index] == 32))
		index++;
	if (str[index] == 43 || str[index] == 45)
	{
		if (str[index] == 45)
			sign *= -1;
		index++;
	}
	while (str[index] >= 48 && str[index] <= 57)
	{
		result = result * 10 + (str[index] - 48);
		index++;
	}
	return (result * sign);
}
