/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:05:44 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 17:05:47 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_t	get_token_type(char *token_value, char *original_str);
char		*remove_quotes(char *value, t_token_t *type);
void		add_to_tokens(t_token **head, char *value, t_token_t type,
				int append);

char	*remove_quotes(char *value, t_token_t *type)
{
	char	*res;
	size_t	len;
	char	*dst;
	int		state;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	res = ft_malloc(len + 1);
	if (!res)
		return (NULL);
	dst = res;
	state = 0;
	process_quote_removal(value, dst, &state);
	if (type && *type != SQ && *type != DQ)
		*type = WORD;
	ft_free(value);
	return (res);
}

void	add_to_tokens(t_token **head, char *value, t_token_t type, int append)
{
	t_token	*new_token;
	t_token	*cur;

	new_token = ft_malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = type;
	new_token->value = value;
	new_token->append = append;
	new_token->quote_ctx = NORMAL;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
	}
}
