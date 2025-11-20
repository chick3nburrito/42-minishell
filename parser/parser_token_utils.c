/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:00:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/01/20 00:00:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_t	check_operator_type(char *token_value)
{
	if (ft_strcmp(token_value, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token_value, "<") == 0)
		return (RIN);
	if (ft_strcmp(token_value, ">") == 0)
		return (ROUT);
	if (ft_strcmp(token_value, ">>") == 0)
		return (AP);
	if (ft_strcmp(token_value, "<<") == 0)
		return (HER);
	return (WORD);
}

static int	has_middle_quote(const char *str, size_t len, char quote)
{
	size_t	i;

	i = 1;
	while (i < len - 1)
	{
		if (str[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

static t_token_t	check_quote_type(const char *original_str, size_t len)
{
	if (original_str[0] == '\'' && original_str[len - 1] == '\'')
	{
		if (!has_middle_quote(original_str, len, '\''))
			return (SQ);
	}
	if (original_str[0] == '"' && original_str[len - 1] == '"')
	{
		if (!has_middle_quote(original_str, len, '"'))
			return (DQ);
	}
	return (WORD);
}

t_token_t	get_token_type(char *token_value, char *original_str)
{
	size_t		len;
	t_token_t	op_type;

	op_type = check_operator_type(token_value);
	if (op_type != WORD)
		return (op_type);
	len = ft_strlen(original_str);
	if (len >= 2)
		return (check_quote_type(original_str, len));
	return (WORD);
}
