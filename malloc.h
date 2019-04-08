/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:59:41 by sromanet          #+#    #+#             */
/*   Updated: 2019/04/03 20:59:43 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
#include <sys/types.h>
# include <sys/mman.h>

# define TINY_SIZE 1024
# define SMALL_SIZE (TINY_SIZE * 4)
# define BLOCKS_LIMIT 100

typedef struct		s_block
{
	int				type;
	void			*ptr;
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_malloc
{
	int				is_init;
	t_block			*tiny;
	size_t			tiny_len;
	size_t			tiny_used;
	t_block			*small;
	size_t			small_len;
	size_t			tiny_used;
	t_block			*large;
	size_t			large_len;
	size_t			large_used;
}					t_malloc;



void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);

#endif