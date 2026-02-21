/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:13:11 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 01:41:57 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars(char *line, t_snail *snail)
{
	if (!line || !snail)
		return (ft_strdup(""));
	return (expand_single_variable(line, snail));
}

static bool	check_unclosed_quotes(const char *s)
{
	t_quote_state	state;

	state = NORMAL;
	while (*s)
	{
		if (*s == '\'' && state == NORMAL)
			state = IN_SQUOTE;
		else if (*s == '\'' && state == IN_SQUOTE)
			state = NORMAL;
		else if (*s == '"' && state == NORMAL)
			state = IN_DQUOTE;
		else if (*s == '"' && state == IN_DQUOTE)
			state = NORMAL;
		s++;
	}
	return (state != NORMAL);
}

static const char	*skip_leading_ws(const char *s)
{
	while (*s && (*s == '\t' || *s == '\n' || *s == '\r' || *s == '\v'
			|| *s == '\f' || *s == ' '))
		s++;
	return (s);
}

bool	is_valid(char *input)
{
	t_snail		*snail;
	const char	*str;

	snail = shell();
	if (!input || !*input)
		return (false);
	if (check_unclosed_quotes(input))
	{
		snail->exit_code = 2;
		ft_error("minishell: syntax error: unclosed quotes\n");
		return (false);
	}
	str = skip_leading_ws(input);
	if (*str == '\0')
		return (false);
	return (true);
}

void	handle_sigint(int sig)
{
	t_snail	*snail;

	(void)sig;
	snail = shell();
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	snail->exit_code = 130;
}
