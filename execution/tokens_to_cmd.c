/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:14:10 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:14:11 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == WORD || current->type == SQ || current->type == DQ)
			count++;
		current = current->next;
	}
	return (count);
}

static int	fill_args_from_tokens(t_card *card, int arg_count)
{
	t_token	*current;
	int		i;

	current = card->tokens;
	i = 0;
	while (current && i < arg_count)
	{
		if (current->type == WORD || current->type == SQ || current->type == DQ)
		{
			card->args[i] = ft_strdup(current->value);
			if (!card->args[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	card->args[i] = NULL;
	return (1);
}

void	fill_cmd_and_args(t_card *card)
{
	int	arg_count;

	if (!card)
		return ;
	card->cmd = NULL;
	card->args = NULL;
	if (!card->tokens)
		return ;
	arg_count = count_word_tokens(card->tokens);
	if (arg_count == 0)
		return ;
	card->args = ft_malloc(sizeof(char *) * (arg_count + 1));
	if (!card->args)
		return ;
	if (!fill_args_from_tokens(card, arg_count))
		return ;
	if (arg_count > 0 && card->args[0])
		card->cmd = ft_strdup(card->args[0]);
}

void	setup_all_cards(t_snail *snail)
{
	t_card	*current;

	if (!snail || !snail->cards)
		return ;
	current = snail->cards;
	while (current)
	{
		fill_cmd_and_args(current);
		current = current->next;
	}
}
