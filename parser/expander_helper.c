/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 04:02:17 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quoted_content(const char *str)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!in_quotes)
				in_quotes = str[i];
			else if (in_quotes == str[i])
				in_quotes = 0;
		}
		else if (str[i] == ' ' && in_quotes)
			return (1);
		i++;
	}
	return (0);
}

int	should_expand_token(t_token *token)
{
	return (token->type == WORD || token->type == DQ);
}

t_token	*splice_tokens(t_splice_params *params, t_token *next)
{
	t_token	*last;

	if (params->prev)
		params->prev->next = params->new_list;
	else
		*(params->head) = params->new_list;
	last = params->new_list;
	while (last->next)
		last = last->next;
	last->next = next;
	ft_free(params->current->value);
	ft_free(params->current);
	return (last);
}

void	handle_token_expansion(t_card *card, t_token **cur, t_token **prev,
		t_snail *snail)
{
	char			*expanded;
	t_token			*new_list;
	t_splice_params	params;
	t_token			*next;

	next = (*cur)->next;
	expanded = expand_single_variable((*cur)->value, snail);
	new_list = split_expanded_token(expanded, (*cur)->type);
	if (!new_list)
	{
		ft_free((*cur)->value);
		(*cur)->value = expanded;
		(*cur)->type = WORD;
		*prev = *cur;
		return ;
	}
	params.head = &card->tokens;
	params.prev = *prev;
	params.current = *cur;
	params.new_list = new_list;
	*prev = splice_tokens(&params, next);
}

void	expand_card_tokens(t_card *card, t_snail *snail, char *expanded)
{
	t_token	*next;
	t_token	*cur;
	t_token	*prev;

	if (!card || !snail)
		return ;
	cur = card->tokens;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (should_expand_token(cur))
			handle_token_expansion(card, &cur, &prev, snail);
		else if (cur->type == SQ)
		{
			expanded = remove_quotes(ft_strdup(cur->value), &cur->type);
			ft_free(cur->value);
			cur->value = expanded;
			cur->type = WORD;
			prev = cur;
		}
		else
			prev = cur;
		cur = next;
	}
}
