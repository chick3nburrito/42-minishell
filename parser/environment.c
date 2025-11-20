/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:35 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:12:36 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_node(char *var, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)ft_malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var = ft_strdup(var);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	if (!new_node->var || !new_node->value)
	{
		ft_free(new_node->var);
		ft_free(new_node->value);
		ft_free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	add_to(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	build_env(t_env **env, char **envp)
{
	char	*pos;
	char	*var;
	char	*value;
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		pos = ft_strchr(envp[i], '=');
		if (pos)
		{
			var = ft_substr(envp[i], 0, pos - envp[i]);
			value = ft_strdup(pos + 1);
			if (var && value)
				add_to(env, new_node(var, value));
			ft_free(var);
			ft_free(value);
		}
		i++;
	}
}

char	*buscando_env(char *var, t_env *env)
{
	t_env	*tmp;
	t_snail	*snail;

	if (!env)
		return (NULL);
	if (ft_strcmp(var, "?") == 0)
	{
		snail = shell();
		return (ft_itoa(snail->exit_code));
	}
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

t_env	*buscando_node(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
