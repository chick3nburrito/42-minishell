/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:35:02 by bamdjar           #+#    #+#             */
/*   Updated: 2024/11/13 13:31:13 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **result)
{
	char	**current;

	current = result;
	while (*current)
	{
		ft_free(*current);
		current++;
	}
	ft_free(result);
}

static void	allocate(char **result, char const *s, char sep)
{
	char		**result1;
	char const	*tmp;

	result1 = result;
	tmp = s;
	while (*s)
	{
		while (*s == sep)
			s++;
		tmp = s;
		while (*tmp && *tmp != sep)
			tmp++;
		if (tmp > s)
		{
			*result1 = ft_substr(s, 0, tmp - s);
			if (!*result1)
			{
				free_all(result);
				return ;
			}
			s = tmp;
			result1++;
		}
	}
	*result1 = NULL;
}

static int	words(char const *s, char sep)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			counter++;
		while (*s && *s != sep)
			s++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;

	if (!s)
		return (NULL);
	size = words(s, c);
	result = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	allocate(result, s, c);
	return (result);
}
