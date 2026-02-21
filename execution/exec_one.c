/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:13:49 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 03:32:44 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_redir(t_card *card, int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = -1;
	*saved_stdout = -1;
	if (card->fd0 != 0)
	{
		*saved_stdin = dup(STDIN_FILENO);
		dup2(card->fd0, STDIN_FILENO);
	}
	if (card->fd1 != 1)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		dup2(card->fd1, STDOUT_FILENO);
	}
}

static void	restore_redirections(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static int	red(t_snail *snail, t_card *card)
{
	int	saved_stdin;
	int	saved_stdout;

	setup_redir(card, &saved_stdin, &saved_stdout);
	snail->exit_code = myblts(card, snail);
	restore_redirections(saved_stdin, saved_stdout);
	return (snail->exit_code);
}

static void	child_redir(t_card *card)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (card->fd0 != 0)
	{
		dup2(card->fd0, STDIN_FILENO);
		if (card->fd0 > 2)
			close(card->fd0);
	}
	if (card->fd1 != 1)
	{
		dup2(card->fd1, STDOUT_FILENO);
		if (card->fd1 > 2)
			close(card->fd1);
	}
}

int	exec_one(t_snail *snail, t_card *card)
{
	pid_t	pid;
	int		exit_code;

	if (!card || !card->cmd || !card->cmd[0])
		return (snail->exit_code = 0, 0);
	if (blt(card))
		return (red(snail, card));
	save_signals_for_fork(snail);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		restore_signals_after_fork(snail);
		return (1);
	}
	if (pid > 0)
	{
		exit_code = handle_parent_process(snail, pid);
		restore_signals_after_fork(snail);
		return (exit_code);
	}
	child_redir(card);
	exec_external_command(card, snail);
	return (1);
}
