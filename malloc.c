#include <malloc.h>

t_data g_data = {.tiny[0] = NULL, .small[0] = NULL, .large[0] = NULL};

void	free(void *ptr)
{
	t_header	*header;
	int				index;

	printf ("////////////APPEL A FREE//////////////\n");
	// printf("calling free with ptr = %p\n", ptr);
	if ((header = find_header_tiny_or_small(ptr, g_data.tiny, g_data.small)))
	{
		// printf("malloc found ! at emplacement : %p\n", header + sizeof(t_header));
		header->used = 0;
	}
	else if ((index = find_header_large(ptr, g_data.large)) != -1)
	{
		// printf("large malloc found.\n");
		if (!unmap_and_shift_large_page(index, g_data.large))
		{
			// printf("unmap failed.\n");
			// perror("");
		}
	}
	// else
	// 	printf("mallo/c not found.\n");
}

void	*malloc(size_t size)
{
	printf ("////////////APPEL A MALLOC//////////////\n");
	if (size <= TINY)
		return (tiny(size, g_data.tiny));
	else if (size <= SMALL)
		return (small(size, g_data.small));
	else
		return (large(size, g_data.large));
	return (NULL);
}

void show_alloc_mem()
{
	do_show_alloc_mem(g_data.tiny, g_data.small, g_data.large);
}
