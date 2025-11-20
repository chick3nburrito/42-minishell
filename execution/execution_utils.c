/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:13:54 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/06 15:13:55 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_table(t_env *env)
{
	char	**table;
	char	*tmp;
	int		i;

	i = env_size(env);
	table = ft_malloc(sizeof(char *) * (i + 1));
	if (!table)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->var, "=");
		table[i] = ft_strjoin(tmp, env->value);
		ft_free(tmp);
		env = env->next;
		i++;
	}
	table[i] = NULL;
	return (table);
}

static char	*check_path_entry(char *path_entry, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path_entry, "/");
	full_path = ft_strjoin(tmp, cmd);
	ft_free(tmp);
	return (full_path);
}

static char	*search_in_path_array(char **args, char *cmd, char **save)
{
	char	*path;
	int		i;

	i = 0;
	while (args[i])
	{
		path = check_path_entry(args[i], cmd);
		if (access(path, F_OK) == 0 && *save == NULL)
			*save = ft_strdup(path);
		if (access(path, F_OK | X_OK) == 0 && !is_directory(path))
		{
			ft_free(*save);
			return (path);
		}
		ft_free(path);
		i++;
	}
	return (NULL);
}

char	*buscando_path(char *cmd, t_env *env)
{
	char	*path;
	char	**args;
	char	*save;
	char	*result;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = buscando_env("PATH", env);
	if (!path)
		return (NULL);
	args = ft_split(path, ':');
	ft_free(path);
	if (!args)
		return (NULL);
	save = NULL;
	result = search_in_path_array(args, cmd, &save);
	free_table(args);
	if (result)
		return (result);
	if (save != NULL)
		return (save);
	return (NULL);
}
