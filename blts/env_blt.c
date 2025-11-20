/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:15:19 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/07 02:35:38 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	blt(t_card *card)
{
	if (!card || !card->cmd)
		return (false);
	if (!ft_strcmp(card->cmd, "echo"))
		return (true);
	else if (!ft_strcmp(card->cmd, "cd"))
		return (true);
	else if (!ft_strcmp(card->cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(card->cmd, "export"))
		return (true);
	else if (!ft_strcmp(card->cmd, "unset"))
		return (true);
	else if (!ft_strcmp(card->cmd, "env"))
		return (true);
	else if (!ft_strcmp(card->cmd, "exit"))
		return (true);
	return (false);
}

int	myblts(t_card *card, t_snail *snail)
{
	if (ft_strcmp(card->cmd, "echo") == 0)
		return (echo_blt(card));
	else if (ft_strcmp(card->cmd, "cd") == 0)
		return (cd_blt(card, &snail->env));
	else if (ft_strcmp(card->cmd, "pwd") == 0)
		return (pwd_blt(card));
	else if (ft_strcmp(card->cmd, "export") == 0)
		return (export_blt(card, &snail->env));
	else if (ft_strcmp(card->cmd, "unset") == 0)
		return (unset_blt(card, &snail->env));
	else if (ft_strcmp(card->cmd, "env") == 0)
		return (env_blt(card, snail->env));
	else if (ft_strcmp(card->cmd, "exit") == 0)
		return (exit_blt(card, snail));
	return (0);
}

void	ft_putenv(t_env *env_node, int fd)
{
	ft_putstr_fd(env_node->var, fd);
	ft_putchar_fd('=', fd);
	ft_putstr_fd(env_node->value, fd);
	ft_putchar_fd('\n', fd);
}

int	env_blt(t_card *card, t_env *env)
{
	if (!env)
		return (EXIT_FAILURE);
	while (env)
	{
		if (env->value != NULL)
			ft_putenv(env, card->fd1);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
