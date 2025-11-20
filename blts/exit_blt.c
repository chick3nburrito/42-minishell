/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:15:26 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/07 18:36:59 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_exit_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	cleany(t_snail *snail, int exit_code)
{
	if (snail->cards)
		cleanup_card_fds(snail->cards);
	rl_clear_history();
	exit(exit_code);
}

int	exit_blt(t_card *card, t_snail *snail)
{
	int		exit_code;
	char	*arg;

	if (isatty(0) && isatty(1))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!card->args[1])
		return ((cleany(snail, snail->exit_code), snail->exit_code));
	arg = card->args[1];
	if (!is_valid_exit_argument(arg))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		cleany(snail, 2);
	}
	if (card->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		snail->exit_code = 1;
		return (1);
	}
	exit_code = ft_atoi(arg) % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (cleany(snail, exit_code), exit_code);
}
