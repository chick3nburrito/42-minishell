/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:05:27 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 17:08:51 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		t_lenght(char *str);
char		*skip_whitespace(char *str);
t_token_t	get_token_type(char *token_value, char *original_str);
char		*remove_quotes(char *value, t_token_t *type);
void		add_to_tokens(t_token **head, char *value, t_token_t type,
				int append);

static int	create_and_add_token(t_token **out_list, char *str, size_t len)
{
	char		*orig;
	t_token_t	tt;

	orig = ft_substr(str, 0, len);
	if (!orig)
	{
		printf("Error: Memory allocation failed\n");
		free_tokens(*out_list);
		return (1);
	}
	tt = get_token_type(orig, orig);
	add_to_tokens(out_list, orig, tt, 0);
	return (0);
}

static int	parse_tokens(t_token **out_list, char **pstr)
{
	char	*str;
	size_t	len;

	str = *pstr;
	while (*str)
	{
		len = t_lenght(str);
		if (len == 0)
		{
			str++;
			str = skip_whitespace(str);
			continue ;
		}
		if (create_and_add_token(out_list, str, len) != 0)
			return (1);
		str += len;
		str = skip_whitespace(str);
	}
	*pstr = str;
	return (0);
}

static int	build_and_process(void)
{
	int	heredoc_result;

	heredoc_result = process_heredocs(shell());
	if (heredoc_result != 0)
		return (heredoc_result);
	shell()->cards = build_cards(shell()->tokens);
	if (redir(shell()) != 0)
		return (1);
	return (0);
}

int	parser(char *input)
{
	t_token	*token_list;
	char	*str;
	int		build_result;

	token_list = NULL;
	str = skip_whitespace(input);
	if (parse_tokens(&token_list, &str) != 0)
		return (1);
	shell()->tokens = token_list;
	if (!syntax_checker(token_list))
	{
		free_tokens(shell()->tokens);
		shell()->tokens = NULL;
		return (1);
	}
	build_result = build_and_process();
	if (build_result != 0)
	{
		if (build_result == 130)
			shell()->exit_code = 130;
		free_tokens(shell()->tokens);
		shell()->tokens = NULL;
		return (1);
	}
	return (0);
}
