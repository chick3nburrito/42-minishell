/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cards.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:29 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 04:07:08 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cards.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:29 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:54:22 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_to_list(t_token **head, t_token *src_token)
{
	t_token	*new;
	t_token	*curr;

	new = ft_malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(src_token->value);
	new->type = src_token->type;
	new->append = src_token->append;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	add_card(t_card **head, t_token *token_list)
{
	t_card	*new;
	t_card	*token;

	new = ft_malloc(sizeof(t_card));
	if (!new)
		return ;
	new->tokens = token_list;
	new->cmd = NULL;
	new->args = NULL;
	new->fd0 = STDIN_FILENO;
	new->fd1 = STDOUT_FILENO;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		token->next = new;
	}
}

void	cleanup_card_fds(t_card *cards)
{
	t_card	*current;

	current = cards;
	while (current)
	{
		if (current->fd0 > 2 && current->fd0 != -1)
		{
			close(current->fd0);
			current->fd0 = -1;
		}
		if (current->fd1 > 2 && current->fd1 != -1)
		{
			close(current->fd1);
			current->fd1 = -1;
		}
		current = current->next;
	}
}

void	free_card_resources(t_card *card)
{
	if (card->args)
		free_table(card->args);
	if (card->cmd)
		ft_free(card->cmd);
	if (card->fd0 > 2 && card->fd0 != -1)
	{
		close(card->fd0);
		card->fd0 = -1;
	}
	if (card->fd1 > 2 && card->fd1 != -1)
	{
		close(card->fd1);
		card->fd1 = -1;
	}
}

t_card	*build_cards(t_token *tokens)
{
	t_card	*cards;
	t_token	*token;
	t_token	*lista;

	cards = NULL;
	token = tokens;
	lista = NULL;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			add_token_to_list(&lista, token);
			token = token->next;
		}
		add_card(&cards, lista);
		lista = NULL;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (cards);
}
