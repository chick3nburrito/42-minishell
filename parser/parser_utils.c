/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:05:36 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 02:45:33 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		t_lenght(char *str);
char		*process_quoted_content(char *str, size_t *len, char quote_char);
char		*skip_whitespace(char *str);

static int	handle_quote_transition(char c, t_quote_state *state)
{
	if (c == '\'' && *state == NORMAL)
	{
		*state = IN_SQUOTE;
		return (1);
	}
	else if (c == '\'' && *state == IN_SQUOTE)
	{
		*state = NORMAL;
		return (1);
	}
	else if (c == '"' && *state == NORMAL)
	{
		*state = IN_DQUOTE;
		return (1);
	}
	else if (c == '"' && *state == IN_DQUOTE)
	{
		*state = NORMAL;
		return (1);
	}
	return (0);
}

static int	is_token_boundary(char c, t_quote_state state)
{
	if (state != NORMAL)
		return (0);
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == '<' || c == '>' || c == '|');
}

size_t	t_lenght(char *str)
{
	size_t			i;
	size_t			start;
	t_quote_state	state;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
					+ 1] == '<'))
			return (2);
		return (1);
	}
	start = i;
	state = NORMAL;
	while (str[i] && !is_token_boundary(str[i], state))
	{
		handle_quote_transition(str[i], &state);
		i++;
	}
	return (i - start);
}

char	*process_quoted_content(char *str, size_t *len, char quote_char)
{
	size_t	i;
	char	*result;

	i = 1;
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == quote_char)
		i++;
	*len = i;
	result = ft_substr(str, 0, i);
	return (result);
}

char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
			|| *str == '\v' || *str == '\f'))
		str++;
	return (str);
}
