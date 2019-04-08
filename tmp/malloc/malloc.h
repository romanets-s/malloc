/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:13:02 by dverbyts          #+#    #+#             */
/*   Updated: 2018/11/24 21:13:05 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
// # include "libft/libft.h"

# define FREE			0
# define USED			1
# define TINY			10
# define SMALL			20
# define LARGE			30

# define TINY_BLOCK		512
# define SMALL_BLOCK	512 * 16
# define MIN_BLOCKS		100

typedef struct			s_block
{
	int					type;
	int					status;
	struct s_block		*next;
	struct s_block		*prev;
	size_t				used_memory_size;
	void				*memory;
}						t_block;

typedef struct			s_global
{
	t_block				*tiny;
	size_t				tiny_length;
	size_t				tiny_used_chunks;
	t_block				*small;
	size_t				small_length;
	size_t				small_used_chunks;
	t_block				*large;
	size_t				large_length;
	size_t				summary_size;
}						t_global;

t_global				*g_global;


void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					*ft_calloc(size_t num, size_t size);
void					init_chunks(t_block *new_memory, size_t size, int type);
t_block					*init_block(size_t size, int type);
t_block					*find_free_chunk(int type);
void 					show_alloc_mem(void);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
