/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:02:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/07 18:29:46 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(t_card *card, char *filename)
{
	int		fd;
	char	*clean_filename;

	clean_filename = remove_quotes_from_expanded(filename);
	if (!clean_filename)
		clean_filename = ft_strdup(filename);
	fd = open(clean_filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(clean_filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		ft_free(clean_filename);
		return (-1);
	}
	if (card->fd0 > 2 && card->fd0 != 0)
	{
		close(card->fd0);
		card->fd0 = 0;
	}
	card->fd0 = fd;
	ft_free(clean_filename);
	return (0);
}

int	open_output_file(t_card *card, char *filename, int append, int fd)
{
	char	*clean_filename;

	clean_filename = remove_quotes_from_expanded(filename);
	if (!clean_filename)
		clean_filename = ft_strdup(filename);
	if (append)
		fd = open(clean_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(clean_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(clean_filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		ft_free(clean_filename);
		return (-1);
	}
	if (card->fd1 > 2 && card->fd1 != 1)
	{
		close(card->fd1);
		card->fd1 = 1;
	}
	return (card->fd1 = fd, ft_free(clean_filename), 0);
}

int	validate_next_token(t_token *next_token)
{
	if (!next_token || (next_token->type != WORD && next_token->type != SQ
			&& next_token->type != DQ))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (next_token)
			ft_putstr_fd(next_token->value, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	handle_rin_token(t_card *card, t_token *next_token)
{
	int	fd;

	if (ft_isdigit_str(next_token->value))
	{
		fd = ft_atoi(next_token->value);
		if (fd > 2)
		{
			if (card->fd0 > 2 && card->fd0 != 0)
			{
				close(card->fd0);
				card->fd0 = 0;
			}
			card->fd0 = fd;
			return (0);
		}
	}
	if (open_input_file(card, next_token->value) == -1)
		return (1);
	return (0);
}

int	handle_output_token(t_card *card, t_token *next_token, int append)
{
	if (open_output_file(card, next_token->value, append, -1) == -1)
		return (1);
	return (0);
}
