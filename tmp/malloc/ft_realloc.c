/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:10:39 by dverbyts          #+#    #+#             */
/*   Updated: 2018/11/24 21:10:47 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*remalloc_chunk(t_block *tmp, size_t size)
{
	void *buf;
	size_t len;

	if (size > tmp->used_memory_size)
		len = tmp->used_memory_size;
	else
		len = size;
	buf = malloc(size);
	buf = ft_memcpy(buf, tmp->memory, len);
	free(tmp->memory);
	return (buf);
}

void	*reconfig_chunk(t_block *tmp, size_t size)
{
	g_global->summary_size += (size - tmp->used_memory_size);
	tmp->used_memory_size = size;
	return (tmp->memory);
}

void *realloc2(t_block *tmp, size_t size)
{
	if (size <= TINY_BLOCK)
	{
		if (tmp->type == TINY)
			reconfig_chunk(tmp, size);
		else
			return (remalloc_chunk(tmp, size));
	}
	else if (size <= SMALL_BLOCK)
	{
		if (tmp->type == SMALL)
			reconfig_chunk(tmp, size);
		else
			return (remalloc_chunk(tmp, size));
	}
	else
		return (remalloc_chunk(tmp, size));
	return (tmp->memory);
}

void *realloc(void *ptr, size_t size)
{
	t_block *tmp;

	if (!ptr && size < 1)
		return (NULL);
	if (ptr && size < 1)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	tmp = (t_block*)((char*)ptr - sizeof(t_block));
	return (realloc2(tmp, size));
}
