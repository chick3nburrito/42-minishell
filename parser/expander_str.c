/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 20:33:27 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*append_char_to_result(char *res, char c);

size_t	process_dollar(const char *s, size_t i, char **res, t_snail *snail)
{
	char	*name;
	char	*val;
	size_t	name_len;

	name = extract_var_name(s + i);
	if (name)
	{
		name_len = ft_strlen(name);
		val = get_var_value(name, snail);
		*res = append_and_free(*res, val);
		ft_free(name);
		ft_free(val);
		return (i + 1 + name_len);
	}
	else
	{
		*res = append_char_to_result(*res, '$');
		return (i + 1);
	}
}

char	*handle_quote_chars(const char *str, size_t *i, t_quote_state *state,
		char *result)
{
	char	c;

	c = str[*i];
	if (c == '\'' && *state == NORMAL)
		*state = IN_SQUOTE;
	else if (c == '\'' && *state == IN_SQUOTE)
		*state = NORMAL;
	else if (c == '"' && *state == NORMAL)
		*state = IN_DQUOTE;
	else if (c == '"' && *state == IN_DQUOTE)
		*state = NORMAL;
	result = append_char_to_result(result, c);
	(*i)++;
	return (result);
}

char	*expand_single_variable(const char *str, t_snail *snail)
{
	char			*result;
	size_t			i;
	t_quote_state	state;

	if (!str)
		return (ft_strdup(""));
	result = ft_strdup("");
	i = 0;
	state = NORMAL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			result = handle_quote_chars(str, &i, &state, result);
		else if (str[i] == '$' && state != IN_SQUOTE)
			i = process_dollar(str, i, &result, snail);
		else
		{
			result = append_char_to_result(result, str[i]);
			i++;
		}
	}
	return (result);
}

static void	handle_quote_removal(const char *str, char *temp,
		t_quote_context *ctx)
{
	if ((str[ctx->i] == '"' || str[ctx->i] == '\'') && ctx->state == NORMAL)
	{
		ctx->quote_char = str[ctx->i];
		if (str[ctx->i] == '"')
			ctx->state = IN_DQUOTE;
		else
			ctx->state = IN_SQUOTE;
		ctx->i++;
	}
	else if (str[ctx->i] == ctx->quote_char && ctx->state != NORMAL)
	{
		ctx->state = NORMAL;
		ctx->quote_char = '\0';
		ctx->i++;
	}
	else
		temp[ctx->j++] = str[ctx->i++];
}

char	*remove_quotes_from_expanded(const char *str)
{
	char			*result;
	char			*temp;
	t_quote_context	ctx;

	if (!str)
		return (ft_strdup(""));
	temp = ft_malloc(ft_strlen(str) + 1);
	if (!temp)
		return (ft_strdup(""));
	ctx.i = 0;
	ctx.j = 0;
	ctx.state = NORMAL;
	ctx.quote_char = '\0';
	while (str[ctx.i])
		handle_quote_removal(str, temp, &ctx);
	temp[ctx.j] = '\0';
	result = ft_strdup(temp);
	ft_free(temp);
	return (result);
}
