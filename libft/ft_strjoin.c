/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:44:57 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/12 20:22:51 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	x;
	char	*result;

	i = ft_strlen(s1);
	x = ft_strlen(s2);
	result = (char *)ft_calloc(i + x + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, i + 1);
	ft_strlcat(result, s2, x + i + 1);
	return (result);
}
