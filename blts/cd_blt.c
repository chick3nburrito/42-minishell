/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:15:04 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/07 02:34:01 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: cd");
		return (NULL);
	}
	return (pwd);
}

static int	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		perror("minishel: cd:");
		return (1);
	}
	return (0);
}

static void	update_env(t_env **env, char *old_pwd, char *new_pwd)
{
	t_env	*node;

	node = buscando_node("OLDPWD", *env);
	if (node)
	{
		ft_free(node->value);
		node->value = ft_strdup(old_pwd);
	}
	else
		add_to(env, new_node("OLDPWD", old_pwd));
	node = buscando_node("PWD", *env);
	if (node)
	{
		ft_free(node->value);
		node->value = ft_strdup(new_pwd);
	}
	else
		add_to(env, new_node("PWD", new_pwd));
}

int	cd_blt(t_card *card, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!card->args[1])
		return (1);
	if (card->args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	old_pwd = get_pwd();
	if (!old_pwd)
		return (1);
	if (change_dir(card->args[1]))
		return ((ft_free(old_pwd), 1));
	new_pwd = get_pwd();
	if (!new_pwd)
	{
		ft_free(old_pwd);
		return (1);
	}
	update_env(env, old_pwd, new_pwd);
	ft_free(old_pwd);
	ft_free(new_pwd);
	return (0);
}
