/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:13:01 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 01:40:49 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_error(char *str);

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		ft_free(current->value);
		ft_free(current);
		current = next;
	}
}

static int	syn_error(t_snail *snail, char *arg)
{
	if (arg && *arg == '"')
		ft_error3("minishell: unexpected EOF while looking for matching `",
			"\"", "'\n");
	else if (arg && *arg == '\'')
		ft_error3("minishell: unexpected EOF while looking for matching `", "'",
			"'\n");
	else if (!arg)
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else
		ft_error3("minishell: syntax error near unexpected token `", arg,
			"'\n");
	snail->exit_code = 2;
	return (0);
}

static int	check_operator_rules(t_token *current, t_token *next,
		t_snail *snail)
{
	if ((current->type == RIN || current->type == ROUT || current->type == AP
			|| current->type == PIPE) && !next)
		return (syn_error(snail, NULL), 0);
	if (current->type == HER && !next)
		return (syn_error(snail, NULL), 0);
	if (current->type == HER && next && (next->type != WORD && next->type != SQ
			&& next->type != DQ))
		return (syn_error(snail, next->value), 0);
	if (!next)
		return (1);
	if ((current->type == RIN || current->type == ROUT || current->type == AP
			|| current->type == HER) && next && (next->type == RIN
			|| next->type == ROUT || next->type == AP || next->type == HER
			|| next->type == PIPE))
		return (syn_error(snail, next->value), 0);
	if (current->type == PIPE && next && next->type == PIPE)
		return (syn_error(snail, next->value), 0);
	if ((current->type == RIN || current->type == ROUT || current->type == AP)
		&& next && next->type != WORD && next->type != SQ && next->type != DQ)
		return (syn_error(snail, next->value), 0);
	if (current->type == PIPE && next && next->type != WORD && next->type != SQ
		&& next->type != DQ && next->type != RIN && next->type != ROUT
		&& next->type != AP && next->type != HER)
		return (syn_error(snail, next->value), 0);
	return (1);
}

int	syntax_checker(t_token *tokens)
{
	t_token	*current;
	t_token	*next;
	t_snail	*snail;

	snail = shell();
	current = tokens;
	if (!current)
		return (0);
	if (current->type == PIPE)
		return (syn_error(snail, current->value), 0);
	while (current)
	{
		next = current->next;
		if (!check_operator_rules(current, next, snail))
			return (0);
		current = current->next;
	}
	return (1);
}

void	ft_error3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(str1, str2);
	tmp1 = ft_strjoin(tmp, str3);
	ft_free(tmp);
	if (tmp1)
	{
		ft_error(tmp1);
		ft_free(tmp1);
	}
	else
	{
		ft_error(str1);
		ft_error(str2);
		ft_error(str3);
	}
}
