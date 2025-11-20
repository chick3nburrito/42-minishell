/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:00:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/01/20 00:00:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_state(char c, int *state)
{
	if (c == '\'' && *state != 2)
	{
		if (*state == 1)
			*state = 0;
		else
			*state = 1;
	}
	else if (c == '"' && *state != 1)
	{
		if (*state == 2)
			*state = 0;
		else
			*state = 2;
	}
}

char	*process_quote_removal(char *value, char *dst, int *state)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(value);
	while (i < len)
	{
		if ((value[i] == '\'' && *state != 2) || (value[i] == '"'
				&& *state != 1))
		{
			handle_quote_state(value[i], state);
			i++;
			continue ;
		}
		*dst++ = value[i++];
	}
	*dst = '\0';
	return (dst);
}
