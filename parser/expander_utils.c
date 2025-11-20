/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:12:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 01:11:23 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_variable(char *str)
{
	char	*dollar_pos;

	if (!str)
		return (0);
	dollar_pos = ft_strchr(str, '$');
	while (dollar_pos)
	{
		if (dollar_pos[1] == '?' || ft_isalpha(dollar_pos[1])
			|| dollar_pos[1] == '_')
			return (1);
		dollar_pos = ft_strchr(dollar_pos + 1, '$');
	}
	return (0);
}

int	get_var_name_len(const char *str)
{
	int	len;

	if (!str || *str != '$')
		return (0);
	str++;
	if (*str == '?')
		return (1);
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

char	*extract_var_name(const char *str)
{
	int		name_len;
	char	*var_name;

	if (!str || *str != '$')
		return (NULL);
	str++;
	name_len = get_var_name_len(str - 1);
	if (name_len == 0)
		return (NULL);
	var_name = ft_substr(str, 0, name_len);
	return (var_name);
}

char	*get_var_value(const char *var_name, t_snail *snail)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(snail->exit_code));
	value = buscando_env((char *)var_name, snail->env);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

char	*append_and_free(char *base, const char *add)
{
	char	*tmp;

	tmp = ft_strjoin(base, add);
	ft_free(base);
	return (tmp);
}
