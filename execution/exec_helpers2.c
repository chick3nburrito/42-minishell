/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 03:34:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_process_status(t_snail *snail, int last_pid, int *status)
{
	if (last_pid > 0)
	{
		waitpid(last_pid, status, 0);
		if (WIFEXITED(*status))
			snail->exit_code = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			snail->exit_code = 128 + WTERMSIG(*status);
	}
}

int	execute_pipeline_command(t_snail *snail, t_card *card, int prev_fd,
		int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir_help(snail, prev_fd, card, pipe_fd);
		exec_external_command(card, snail);
	}
	return (pid);
}

void	process_pipeline_card(t_snail *snail, t_card *card, int *prev_fd,
		int *final_pid)
{
	int	pipe_fd[2];
	int	last_pid;

	if (card->next && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	if (card->cmd && card->args)
	{
		last_pid = execute_pipeline_command(snail, card, *prev_fd, pipe_fd);
		if (last_pid == -1)
			return ;
		*final_pid = last_pid;
	}
	if (*prev_fd != -1)
		close(*prev_fd);
	if (card->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}
