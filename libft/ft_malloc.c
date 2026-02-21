/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:14:38 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/07 02:43:15 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static t_gc_node	**get_gc_list(void)
{
	static t_gc_node	*gc_list = NULL;

	return (&gc_list);
}

void	*ft_malloc(size_t size)
{
	t_gc_node	**gc_list;
	t_gc_node	*new_node;
	void		*alloc_ptr;

	gc_list = get_gc_list();
	alloc_ptr = malloc(size);
	if (!alloc_ptr)
	{
		perror("minishell: malloc");
		exit(2);
	}
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		free(alloc_ptr);
		perror("minishell: malloc");
		exit(2);
	}
	new_node->ptr = alloc_ptr;
	new_node->next = *gc_list;
	*gc_list = new_node;
	return (alloc_ptr);
}

void	ft_free(void *ptr)
{
	t_gc_node	**gc_list;
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!ptr)
		return ;
	gc_list = get_gc_list();
	current = *gc_list;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*gc_list = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	free(ptr);
}

void	ft_free_all(void)
{
	t_gc_node	**gc_list;
	t_gc_node	*current;
	t_gc_node	*next;

	gc_list = get_gc_list();
	current = *gc_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->ptr != NULL)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		free(current);
		current = next;
	}
	*gc_list = NULL;
}
