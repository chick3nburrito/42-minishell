/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aquidoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:30:48 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 03:19:26 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_SIZE 37

pid_t		handle_heredoc_child(int pipe_fd[2], const char *delimiter,
				int expand, t_snail *snail);

static char	*name_generate(void)
{
	const char		*char_buff = "laBaLeNasEgenA9!xV&yHdg7d@Lp4s+Zq(3G";
	int				fd;
	unsigned char	buf;
	char			*path;
	int				i;

	path = ft_malloc(HEREDOC_SIZE + 6);
	if (!path)
		return (NULL);
	ft_strlcpy(path, "/tmp/", 6);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (ft_free(path), NULL);
	i = 0;
	while (i < HEREDOC_SIZE)
	{
		if (read(fd, &buf, 1) == -1)
			return (close(fd), ft_free(path), NULL);
		path[5 + i] = char_buff[(unsigned char)buf % ft_strlen(char_buff)];
		i++;
	}
	close(fd);
	path[5 + i] = '\0';
	return (path);
}

static int	setup_heredoc_file(char **filename)
{
	int	fd;

	*filename = name_generate();
	if (!*filename)
		return (-1);
	fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (ft_free(*filename), -1);
	return (fd);
}

static int	copy_from_pipe_to_file(int pipe_fd, int file_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(pipe_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(file_fd, buffer, bytes_read) != bytes_read)
			return (-1);
		bytes_read = read(pipe_fd, buffer, sizeof(buffer));
	}
	if (bytes_read == -1)
		return (-1);
	return (0);
}

static int	finalize_heredoc(char *filename, int status)
{
	int	fd;

	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(filename);
		ft_free(filename);
		return (-2);
	}
	fd = open(filename, O_RDONLY);
	unlink(filename);
	ft_free(filename);
	return (fd);
}

int	create_heredoc(const char *delimiter, int expand, t_snail *snail)
{
	int		pipe_fd[2];
	char	*filename;
	pid_t	pid;

	int (fd), (status);
	fd = setup_heredoc_file(&filename);
	if (fd == -1)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (close(fd), ft_free(filename), -1);
	pid = handle_heredoc_child(pipe_fd, delimiter, expand, snail);
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), close(fd),
			ft_free(filename), -1);
	close(pipe_fd[1]);
	if (copy_from_pipe_to_file(pipe_fd[0], fd) == -1)
	{
		close(pipe_fd[0]);
		close(fd);
		waitpid(pid, &status, 0);
		return (restore_signals_after_heredoc(snail), ft_free(filename), -2);
	}
	waitpid(pid, &status, 0);
	return (close(pipe_fd[0]), close(fd), restore_signals_after_heredoc(snail),
		finalize_heredoc(filename, status));
}
