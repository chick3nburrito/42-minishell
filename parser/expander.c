/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 03:37:06 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_snail *snail)
{
	t_card	*cur;

	if (!snail)
		return ;
	cur = snail->cards;
	while (cur)
	{
		expand_card_tokens(cur, snail, NULL);
		cur = cur->next;
	}
}

static t_token	*handle_token_expansion(t_token **tokens, t_token *cur,
		t_token *prev, t_snail *snail)
{
	char			*expanded;
	t_token			*new_list;
	t_splice_params	params;
	t_token			*next;

	next = cur->next;
	expanded = expand_single_variable(cur->value, snail);
	new_list = split_expanded_token(expanded, cur->type);
	if (new_list)
	{
		params.head = tokens;
		params.prev = prev;
		params.current = cur;
		params.new_list = new_list;
		prev = splice_tokens(&params, next);
	}
	else
	{
		ft_free(cur->value);
		cur->value = expanded;
		cur->type = WORD;
		prev = cur;
	}
	return (prev);
}

void	expand_token_list(t_token **tokens, t_snail *snail)
{
	char	*expanded;
	t_token	*new_list;
	t_token	*cur;
	t_token	*prev;
	t_token	*next;

	(void)expanded;
	(void)new_list;
	if (!tokens || !*tokens || !snail)
		return ;
	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (should_expand_token(cur))
			prev = handle_token_expansion(tokens, cur, prev, snail);
		else
			prev = cur;
		cur = next;
	}
}
