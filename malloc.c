#include <malloc.h>

t_data g_data = {.tiny[0] = NULL, .small[0] = NULL, .large[0] = NULL};

void	free(void *ptr)
{
	t_header	*header;
	int			index;
	int			new_size;

	if (!ptr)
		return ;
	new_size = 0;
	if ((header = find_header_tiny_or_small(ptr, &g_data, &new_size)))
	{
		if (new_size == -1)
			return ;
		else if (new_size)
			header->size = new_size;
		header->used = 0;
	}
	else if ((index = find_header_large(ptr, g_data.large)) != -1)
	{
		unmap_and_shift_page(index, g_data.large);
	}
}

void	*malloc(size_t size)
{
	if (size <= TINY)
		return (tiny(size, g_data.tiny));
	else if (size <= SMALL)
		return (small(size, g_data.small));
	else
		return (large(size, g_data.large));
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	if (size == 0 && ptr)
	{
		free(ptr);
		return (malloc(0));
	}
	if (!ptr)
	{
		return (malloc(size));
	}
	return (do_realloc(ptr, size, &g_data));
}

void	show_alloc_mem(void)
{
	do_show_alloc_mem(g_data.tiny, g_data.small, g_data.large);
}
