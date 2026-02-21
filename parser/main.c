/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:46 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 17:08:20 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_snail	*shell(void)
{
	static t_snail	snail;

	return (&snail);
}

static void	init(char **envp)
{
	t_snail	*snail;

	snail = shell();
	build_env(&snail->env, envp);
	snail->in_heredoc = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static int	process_input_line(char *input)
{
	if (!is_valid(input))
		return (1);
	add_history(input);
	if (parser(input))
		return (1);
	expand_tokens(shell());
	setup_all_cards(shell());
	execution(shell());
	cleanup_shell();
	return (0);
}

static void	run_loop(t_snail *snail, char *input)
{
	(void)snail;
	while (1)
	{
		input = readline(PROMT);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (process_input_line(input))
		{
			free(input);
			continue ;
		}
		free(input);
	}
}

int	main(int ac, char **arv, char **envp)
{
	t_snail	*snail;
	int		i;

	(void)ac;
	(void)arv;
	init(envp);
	run_loop(shell(), NULL);
	snail = shell();
	i = snail->exit_code;
	ft_free_all();
	return (i);
}
