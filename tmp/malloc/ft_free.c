/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:10:39 by dverbyts          #+#    #+#             */
/*   Updated: 2018/11/24 21:10:47 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

void	dealloc_memory(t_block *tmp)
{
	size_t	memory_allocation_size;
	size_t	size;
	t_block *buf;

	if (tmp->type == LARGE)
	{
		memory_allocation_size = (sizeof(t_block) + tmp->used_memory_size);
		buf = tmp->prev;
		if (tmp->next != NULL)
		{
			tmp->next->prev = buf;
			if (buf != NULL)
				buf->next = tmp->next;
		}
	}
	else
	{
		tmp->type == TINY ? (size = TINY_BLOCK) : (size = SMALL_BLOCK);
		memory_allocation_size = ((sizeof(t_block) + size) * MIN_BLOCKS);
	}
	while (memory_allocation_size % getpagesize() != 0)
		memory_allocation_size++;
	munmap(tmp, memory_allocation_size);
}

void	 check_block(int type)
{
	t_block *tmp;
	t_block *buf;
	int len;
	int lenght;
	int chunks;

	len = 0;
	type == TINY ? (tmp = g_global->tiny) : (tmp = g_global->small);
	type == TINY ? (lenght = g_global->tiny_length) :
			(lenght = g_global->small_length);
	type == TINY ? (chunks = g_global->tiny_used_chunks) :
			(chunks = g_global->small_used_chunks);
	if (lenght <= MIN_BLOCKS || chunks > 80)
		return ;
	while (len++ < MIN_BLOCKS && tmp->next != NULL)
		tmp = tmp->next;
	buf = tmp->next;
	while (tmp != NULL)
	{
		if (tmp->status != FREE)
			return ;
		tmp = tmp->next;
	}
	dealloc_memory(buf);
}

void	free(void *ptr)
{
	t_block *tmp;

	if (ptr == NULL)
		return ;
	tmp = (t_block*)((char*)ptr - sizeof(t_block));
	if (tmp->type == LARGE)
	{
		g_global->summary_size -= tmp->used_memory_size;
		g_global->large_length--;
		dealloc_memory(tmp);
	}
	else
	{
		tmp->type == TINY ? (g_global->tiny_used_chunks--) :
					(g_global->small_used_chunks--) ;
		g_global->summary_size -= tmp->used_memory_size;
		tmp->used_memory_size = 0;
		tmp->status = FREE;
		tmp->type == TINY ? check_block(TINY) : check_block(SMALL);
	}
}
