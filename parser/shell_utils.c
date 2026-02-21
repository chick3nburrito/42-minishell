/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/07 18:30:01 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cleanup_shell(void)
{
	t_snail	*snail;

	snail = shell();
	if (snail->cards)
	{
		free_pcard(&snail->cards);
		snail->cards = NULL;
	}
	if (snail->tokens)
	{
		free_tokens(snail->tokens);
		snail->tokens = NULL;
	}
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		ft_free(table[i]);
		i++;
	}
	ft_free(table);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
