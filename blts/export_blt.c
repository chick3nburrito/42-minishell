/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:15:31 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 20:45:56 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_id(const char *str)
{
	int	i;

	if (!str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
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

static void	no_args(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->var, fd);
		if (tmp->value != NULL)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else
		{
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
}

static void	set_var(t_env **env, char *name, char *value, t_env *node)
{
	t_env	*n;

	node = buscando_node(name, *env);
	if (!node)
	{
		if (value)
			n = new_node(name, ft_strdup(value));
		else
			n = new_node(name, NULL);
		if (n)
		{
			if (!value)
			{
				ft_free(n->value);
			//	n->value = NULL;
			}
		}
		add_to(env, n);
	}
	else if (value)
	{
		ft_free(node->value);
		node->value = ft_strdup(value);
	}
}

static int	check_input(char *arg, t_env **env)
{
	char	*pos;
	char	*var_name;
	char	*val;

	pos = ft_strchr(arg, '=');
	if (pos)
		var_name = ft_substr(arg, 0, pos - arg);
	else
		var_name = ft_strdup(arg);
	if (!valid_id(var_name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (ft_free(var_name), 1);
	}
	if (pos)
	{
		val = ft_strdup(pos + 1);
		set_var(env, var_name, val, NULL);
		ft_free(val);
	}
	else
		set_var(env, var_name, NULL, NULL);
	return (ft_free(var_name), 0);
}

int	export_blt(t_card *card, t_env **env)
{
	int	i;
	int	error_count;

	i = 1;
	error_count = 0;
	if (!card->args[1])
		no_args(*env, card->fd1);
	else
	{
		while (card->args[i])
		{
			if (check_input(card->args[i], env))
				error_count = 1;
			i++;
		}
	}
	return (error_count);
}
