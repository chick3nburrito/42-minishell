/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:12:08 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 04:07:34 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_card_resources(t_card *card);

char	*append_char_to_result(char *res, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	res = append_and_free(res, tmp);
	return (res);
}

t_token	*create_token_node(char *value, t_token_t type)
{
	t_token	*node;

	node = ft_malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->append = 0;
	node->quote_ctx = NORMAL;
	node->next = NULL;
	return (node);
}

t_token	*create_token_list_from_words(char **words)
{
	t_token	*list;
	t_token	*cur;
	int		i;

	list = NULL;
	cur = NULL;
	i = 0;
	while (words[i])
	{
		if (!list)
		{
			list = create_token_node(ft_strdup(words[i]), WORD);
			cur = list;
		}
		else
		{
			cur->next = create_token_node(ft_strdup(words[i]), WORD);
			cur = cur->next;
		}
		i++;
	}
	return (list);
}

t_token	*split_expanded_token(const char *expanded_str, t_token_t original_type)
{
	t_token	*list;
	char	*final;
	char	**words;

	if (!expanded_str)
		return (NULL);
	final = remove_quotes_from_expanded(expanded_str);
	if (original_type == DQ || has_quoted_content(expanded_str))
		return (create_token_node(final, WORD));
	words = ft_split(final, ' ');
	ft_free(final);
	if (!words)
		return (NULL);
	list = create_token_list_from_words(words);
	free_table(words);
	if (!list)
		return (create_token_node(ft_strdup(""), WORD));
	return (list);
}

void	free_pcard(t_card **head)
{
	t_card	*current;
	t_card	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free_tokens(current->tokens);
		free_card_resources(current);
		ft_free(current);
		current = next;
	}
	*head = NULL;
}
