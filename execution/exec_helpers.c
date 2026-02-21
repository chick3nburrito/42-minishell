/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_path(char *path, t_card *card)
{
	if (!path)
	{
		ft_error3("minishell: ", card->cmd, ": command not found\n");
		exit(127);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_error3("minishell: ", path, ": Permission denied\n");
		ft_free(path);
		exit(126);
	}
	if (is_directory(path))
	{
		ft_error3("minishell: ", path, ": Is a directory\n");
		ft_free(path);
		exit(126);
	}
}

int	handle_parent_process(t_snail *snail, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		snail->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		snail->exit_code = 128 + WTERMSIG(status);
	return (snail->exit_code);
}

void	exec_external_command(t_card *card, t_snail *snail)
{
	char	*path;
	char	**envp;

	path = buscando_path(card->cmd, snail->env);
	validate_path(path, card);
	envp = env_to_table(snail->env);
	execve(path, card->args, envp);
	handle_execve_error(card, path, envp);
	ft_free(path);
	free_table(envp);
}
