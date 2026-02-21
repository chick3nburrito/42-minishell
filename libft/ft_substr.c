/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 08:15:56 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/02 13:48:08 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tab;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	i = ft_strlen(s + start);
	if (i < len)
	{
		len = i;
	}
	tab = ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s + start, len + 1);
	return (tab);
}
