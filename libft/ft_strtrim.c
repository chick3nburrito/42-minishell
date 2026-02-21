/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:40:10 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/07 02:13:03 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	min;
	size_t	max;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	max = ft_strlen(s1) - 1;
	min = 0;
	while (s1[min] && ft_strchr((char *)set, s1[min]))
		min++;
	while (s1[max] && ft_strchr((char *)set, s1[max]))
		max--;
	size = max - min + 1;
	result = ft_substr(s1, min, size);
	return (result);
}
