/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:10:39 by dverbyts          #+#    #+#             */
/*   Updated: 2018/11/24 21:10:47 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_global	*g_global;

void	*manage_memory_t(size_t size)
{
	t_block *tmp;
	t_block *buf;

	tmp = NULL;
	buf = g_global->tiny;
	if (g_global->tiny_used_chunks < g_global->tiny_length)
		tmp = find_free_chunk(TINY);
	else
	{
		tmp = init_block(TINY_BLOCK, TINY);
		if (tmp == NULL)
			return (NULL);
		while (buf->next != NULL)
			buf = buf->next;
		buf->next = tmp;
		g_global->tiny_length += MIN_BLOCKS;
		tmp->prev = buf;
	}
	if (tmp == NULL)
		return (NULL);
	tmp->status = USED;
	tmp->used_memory_size = size;
	g_global->tiny_used_chunks++;
	g_global->summary_size += size;
	return (tmp->memory);
}

void	*manage_memory_s(size_t size)
{
	t_block *tmp;
	t_block *buf;

	tmp = NULL;
	buf = g_global->small;
	if (g_global->small_used_chunks < g_global->small_length)
		tmp = find_free_chunk(SMALL);
	else
	{
		tmp = init_block(SMALL_BLOCK, SMALL);
		if (tmp == NULL)
			return (NULL);
		while (buf->next != NULL)
			buf = buf->next;
		buf->next = tmp;
		g_global->small_length += MIN_BLOCKS;
		tmp->prev = buf;
	}
	if (tmp == NULL)
		return (NULL);
	tmp->status = USED;
	tmp->used_memory_size = size;
	g_global->small_used_chunks++;
	g_global->summary_size += size;
	return (tmp->memory);
}

void	*manage_memory_l(size_t size)
{
	t_block *tmp;
	t_block *buf;

	tmp = g_global->large;
	if (tmp == NULL)
	{
		tmp = init_block(size, SMALL);
		if (tmp == NULL)
			return (NULL);
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		buf = tmp;
		if ((tmp->next = init_block(size, SMALL)) == NULL)
			return (NULL);
		tmp = tmp->next;
		tmp->prev = buf;
	}
		tmp->status = USED;
	tmp->used_memory_size = size;
	g_global->large_length++;
	g_global->summary_size += size;
	return (tmp->memory);
}

void	*init_global(void)
{
	if (!g_global->tiny && !g_global->small && !g_global->large)
	{	 
		if (!(g_global->tiny = init_block(TINY_BLOCK, TINY)))
			return (NULL);
		g_global->tiny_length = MIN_BLOCKS;
		g_global->tiny_used_chunks = 0;
		if (!(g_global->small = init_block(SMALL_BLOCK, SMALL)))
			return (NULL);
		g_global->small_length = MIN_BLOCKS;
		g_global->small_used_chunks = 0;
		g_global->large = NULL;
		g_global->large_length = 0;
		g_global->summary_size = 0;
	}
	return (g_global->tiny);
}

void	*malloc(size_t size)
{
	void		*new_memory;

	new_memory = NULL;
	if (size < 1)
		return (NULL);
	if (init_global() == NULL)
		return (NULL);
	if (size <= TINY_BLOCK)
		new_memory = manage_memory_t(size);
	else if (size <= SMALL_BLOCK)
		new_memory = manage_memory_s(size);
	else
		new_memory = manage_memory_l(size);	
	return (new_memory);
}
