/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:39:44 by bamdjar           #+#    #+#             */
/*   Updated: 2025/04/07 20:31:52 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	*ft_atoi(const char *str)
{
	int			index;
	static int	result[2];

	result[0] = 0;
	result[1] = 1;
	index = 0;
	while (str[index] && (str[index] == ' ' || str[index] == '\t'))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			result[1] = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result[0] = result[0] * 10 + (str[index] - 48);
		index++;
	}
	return (result);
}

double	atod(char *s)
{
	double	val[2];
	size_t	i;

	i = 0;
	val[0] = ft_atoi(s)[0];
	val[1] = ft_atoi(s)[1];
	while (s[i] && s[i] != '.' && s[i] != ',')
		i++;
	if (s[i] == ',' || s[i] == '.')
	{
		i++;
		val[0] += ft_atoi(s + i)[0] / pow(10, ft_strlen(s + i));
	}
	return (val[0] * val[1]);
}
