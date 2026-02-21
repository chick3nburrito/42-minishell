/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:13:06 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 00:42:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_signals_for_heredoc(t_snail *snail)
{
	(void)snail;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals_after_heredoc(t_snail *snail)
{
	(void)snail;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	save_signals_for_fork(t_snail *snail)
{
	(void)snail;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals_after_fork(t_snail *snail)
{
	(void)snail;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}
