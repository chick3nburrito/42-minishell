/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:14:06 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:14:07 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_input_redir(int prev_fd, t_card *card)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (card->fd0 != 0 && prev_fd == -1)
	{
		dup2(card->fd0, STDIN_FILENO);
		if (card->fd0 > 2)
			close(card->fd0);
	}
}

void	redir_help(t_snail *snail, int prev_fd, t_card *card, int *pipe_fd)
{
	setup_input_redir(prev_fd, card);
	if (card->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	else if (card->fd1 != 1)
	{
		dup2(card->fd1, STDOUT_FILENO);
		if (card->fd1 > 2)
			close(card->fd1);
	}
	if (blt(card))
		exit(myblts(card, snail));
}

bool	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

static void	cleanup_and_exit(char *path, char **envp, int exit_code)
{
	ft_free(path);
	free_table(envp);
	exit(exit_code);
}

void	handle_execve_error(t_card *card, char *path, char **envp)
{
	if (errno == EACCES)
	{
		ft_error3("minishell: ", card->cmd, ": Permission denied\n");
		cleanup_and_exit(path, envp, 126);
	}
	else if (errno == ENOENT)
	{
		ft_error3("minishell: ", card->cmd, ": No such file or directory\n");
		cleanup_and_exit(path, envp, 127);
	}
	else if (errno == ENOEXEC)
	{
		ft_error3("minishell: ", card->cmd, ": command not found\n");
		cleanup_and_exit(path, envp, 127);
	}
	else
	{
		perror("minishell: execve");
		cleanup_and_exit(path, envp, 1);
	}
}
