/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:10:39 by dverbyts          #+#    #+#             */
/*   Updated: 2018/11/24 21:10:47 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

void	*ft_calloc(size_t num, size_t size)
{
	void *tmp;
	
	tmp = malloc(num * size);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, (num * size));
	return (tmp);
}

void init_chunks(t_block *new_memory, size_t size, int type)
{
	int len;
	t_block *tmp;

	len = 1;
	tmp = NULL;
	while (len <= 100)
	{
		tmp = (t_block *)(new_memory->memory + size);
		tmp->type = type;
		tmp->status = FREE;
		tmp->next = NULL;
		tmp->used_memory_size = 0;
		tmp->memory = (void *)tmp + sizeof(t_block);
		new_memory->next = tmp;
		new_memory = new_memory->next;
	}
}

t_block		*init_block(size_t size, int type)
{
	t_block	*new_memory;
	size_t	memory_allocation_size;

	if (type == LARGE)
		memory_allocation_size = (sizeof(t_block) + size);
	else
		memory_allocation_size = ((sizeof(t_block) + size) * MIN_BLOCKS);
	while (memory_allocation_size % getpagesize() != 0)
		memory_allocation_size++;
	new_memory = mmap(0, memory_allocation_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	new_memory->type = type;
	new_memory->status = FREE;
	new_memory->next = NULL;
	new_memory->prev = NULL;
	new_memory->used_memory_size = 0;
	if (type == LARGE)
		new_memory->used_memory_size = size;
	new_memory->memory = (void *)new_memory + sizeof(t_block);
	if (type != LARGE)
		init_chunks(new_memory, size, type);
	return (new_memory);
}

t_block	*find_free_chunk(int type)
{
	t_block	*tmp;

	type == TINY ? (tmp = g_global->tiny) : (tmp = g_global->small);
	while (tmp->next != NULL)
	{
		if (tmp->status == FREE)
			return (tmp);
		tmp = tmp->next;
	}
	type == TINY ? (tmp->next = init_block(TINY_BLOCK, TINY)) :
			(tmp->next = init_block(SMALL_BLOCK, SMALL));
	type == TINY ? (g_global->tiny_length += MIN_BLOCKS) : 
			(g_global->small_length += MIN_BLOCKS);
	return (tmp->next);
}
