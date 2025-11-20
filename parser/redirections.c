/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:57 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:43:35 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isdigit_str(char *str);
int			open_input_file(t_card *card, char *filename);
int			open_output_file(t_card *card, char *filename, int append);
int			validate_next_token(t_token *next_token);
int			handle_rin_token(t_card *card, t_token *next_token);
int			handle_output_token(t_card *card, t_token *next_token, int append);

static int	handle_redirection_token(t_card *card, t_token *token,
		t_token *next_token)
{
	if (validate_next_token(next_token))
		return (1);
	if (token->type == RIN)
		return (handle_rin_token(card, next_token));
	else if (token->type == ROUT)
		return (handle_output_token(card, next_token, 0));
	else if (token->type == AP)
		return (handle_output_token(card, next_token, 1));
	return (0);
}

static void	remove_redirection_tokens(t_token **tokens, t_token *redir_token,
		t_token *filename_token)
{
	t_token	*current;
	t_token	*prev;
	t_token	*to_free;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current == redir_token || current == filename_token)
		{
			if (prev)
				prev->next = current->next;
			else
				*tokens = current->next;
			to_free = current;
			current = current->next;
			ft_free(to_free->value);
			ft_free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static int	process_card_redirections(t_card *card, t_token *current)
{
	t_token	*next;
	int		result;

	current = card->tokens;
	while (current)
	{
		next = current->next;
		if (current->type == RIN || current->type == ROUT
			|| current->type == AP)
		{
			result = handle_redirection_token(card, current, next);
			if (result != 0)
				return (result);
			remove_redirection_tokens(&card->tokens, current, next);
			current = card->tokens;
		}
		else
			current = current->next;
	}
	return (0);
}

int	redir(t_snail *snail)
{
	t_card	*current_card;
	int		result;

	if (!snail || !snail->cards)
		return (0);
	current_card = snail->cards;
	while (current_card)
	{
		result = process_card_redirections(current_card, NULL);
		if (result != 0)
		{
			snail->exit_code = 1;
			return (result);
		}
		current_card = current_card->next;
	}
	return (0);
}
