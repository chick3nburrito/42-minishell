/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:15:11 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:15:12 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_n(char ***args)
{
	bool	flag;

	flag = false;
	while (**args && valid(**args))
	{
		flag = true;
		(*args)++;
	}
	return (flag);
}

int	echo_blt(t_card *card)
{
	char	**args;
	bool	suppress_newline;

	args = card->args + 1;
	suppress_newline = check_n(&args);
	while (*args)
	{
		ft_putstr_fd(*args, card->fd1);
		if (*(args + 1))
			ft_putchar_fd(' ', card->fd1);
		args++;
	}
	if (!suppress_newline)
		ft_putchar_fd('\n', card->fd1);
	return (0);
}
