#include "malloc.h"

t_malloc	g_malloc;

void	init_every_block(t_block *start, size_t size, int block_count)
{
	t_block	*ptr;

	t_block *kk = start;

	while (block_count--)
	{
		ptr = (t_block *)start + (sizeof(t_block) + size);
		//ptr->type = size;
		//ptr->ptr = (void *)ptr + sizeof(t_block);
		//ptr->prev = start;
		start->next = ptr;
		start = start->next;
	}
}

t_block		*init_block(size_t size, int block_count)
{
	static	int 	page_size;
	t_block	*start;
	size_t	all_size;

	if (!page_size)
		page_size = getpagesize();
	all_size = block_count * (size + sizeof(t_block));
	all_size = all_size + (page_size - all_size % page_size);
	start = (t_block *)mmap(NULL, all_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (start == MAP_FAILED)
		return (NULL);
	//start->type = size;
	//start->ptr = (void *)start + sizeof(t_block);
	init_every_block(start, size, block_count);
	return (start);
}

int		init_malloc(void)
{
	if (!g_malloc.is_init)
	{
		if (!g_malloc.tiny)
		{
			g_malloc.tiny = init_block(TINY_SIZE, BLOCKS_LIMIT);
			g_malloc.tiny_len = BLOCKS_LIMIT;
			//g_malloc.tiny_used = 0;
		}
		if (!g_malloc.small)
		{
			g_malloc.small = init_block(SMALL_SIZE, BLOCKS_LIMIT);
			g_malloc.small_len = BLOCKS_LIMIT;
			//g_malloc.small_used = 0;
		}
		if (!g_malloc.tiny || !g_malloc.small)
			return (g_malloc.is_init);
		g_malloc.is_init = 1;
	}
	return (g_malloc.is_init);
}

void	*malloc(size_t size)
{
	void	*p;

	printf("%zu\n", size);
	if(!size || !init_malloc())
		return (NULL);
	if (size <= TINY_SIZE)
		; // is tiny
	else if (size <= SMALL_SIZE)
		; // small
	else
		; // large
	return (p);
}