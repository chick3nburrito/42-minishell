/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_blt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:15:45 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:15:46 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_id(const char *str)
{
	int	i;

	if (!str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	r_var(t_env **env, char *var)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->var, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			ft_free(current->var);
			ft_free(current->value);
			ft_free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_blt(t_card *card, t_env **env)
{
	int	i;

	if (!card->args[1])
	{
		return (0);
	}
	i = 1;
	while (card->args[i])
	{
		if (!valid_id(card->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(card->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		else
			r_var(env, card->args[i]);
		i++;
	}
	return (0);
}
