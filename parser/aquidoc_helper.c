/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aquidoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 02:38:04 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 03:38:08 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			create_heredoc(const char *delimiter, int expand, t_snail *snail);

static int	heredoc_loop(int fd, const char *delimiter, int expand,
		t_snail *snail)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warn: BRACE_SHOULD_EOL     (lineing: "
				"here-document delimited by ", 2);
			return (ft_putstr_fd("end-of-file\n", 2), 1);
		}
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), 0);
		if (expand)
		{
			expanded = expand_vars(line, snail);
			write(fd, expanded, ft_strlen(expanded));
			ft_free(expanded);
		}
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	process_heredoc_input_child(int fd, const char *delimiter, int expand,
		t_snail *snail)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_loop(fd, delimiter, expand, snail))
		exit(1);
	exit(0);
}

pid_t	handle_heredoc_child(int pipe_fd[2], const char *delimiter, int expand,
		t_snail *snail)
{
	pid_t	pid;

	save_signals_for_heredoc(snail);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		restore_signals_after_heredoc(snail);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		process_heredoc_input_child(pipe_fd[1], delimiter, expand, snail);
	}
	return (pid);
}

static int	handle_heredoc_token(t_token *current, t_token *next,
		t_snail *snail)
{
	char	*delimiter;
	int		expand;
	int		fd;

	delimiter = ft_strdup(next->value);
	if (!delimiter)
		return (1);
	expand = (next->type == WORD);
	if (next->type == SQ || next->type == DQ)
	{
		delimiter = remove_quotes(delimiter, &next->type);
		if (!delimiter)
			return (1);
		expand = 0;
	}
	fd = create_heredoc(delimiter, expand, snail);
	ft_free(delimiter);
	if (fd == -2)
		return (130);
	if (fd == -1)
		return (1);
	current->type = RIN;
	ft_free(current->value);
	current->value = ft_strdup("<");
	return (ft_free(next->value), next->value = ft_itoa(fd), 0);
}

int	process_heredocs(t_snail *snail)
{
	t_token	*current;
	t_token	*next;
	int		result;

	if (!snail)
		return (1);
	current = snail->tokens;
	while (current)
	{
		next = current->next;
		if (current->type == HER && next)
		{
			result = handle_heredoc_token(current, next, snail);
			if (result != 0)
				return (result);
		}
		current = current->next;
	}
	return (0);
}
