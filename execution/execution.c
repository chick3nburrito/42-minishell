/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:14:01 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:14:02 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mainloop(t_snail *snail, int prev_fd, int *status, t_card *card)
{
	int	final_pid;

	final_pid = 0;
	save_signals_for_fork(snail);
	while (card)
	{
		process_pipeline_card(snail, card, &prev_fd, &final_pid);
		card = card->next;
	}
	handle_process_status(snail, final_pid, status);
	restore_signals_after_fork(snail);
}

void	execution(t_snail *snail)
{
	int		prev_fd;
	int		status;
	t_card	*card;

	if (!snail->cards)
		return ;
	if (!snail->cards->next)
	{
		exec_one(snail, snail->cards);
		return ;
	}
	prev_fd = -1;
	card = snail->cards;
	mainloop(snail, prev_fd, &status, card);
	while (wait(&status) > 0)
		;
	return ;
}
