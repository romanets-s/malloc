#include "malloc.h"

static	t_malloc			*g_malloc;

int		init_malloc(void)
{
	if (!g_malloc->is_init)
	{

	}
	return (1)
}

void	*malloc(size_t size)
{
	void	*p;

	if(!size || !init_malloc())
		return (NULL);
}