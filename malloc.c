#include <malloc.h>

t_data g_data = {.tiny[0] = NULL, .small[0] = NULL, .large[0] = NULL};

void	free(void *ptr)
{
	t_header	*header;
	int				index;
	int 		new_size;

	//printf ("////////////APPEL A FREE//////////////\n");
	if (!ptr)
		return ;
	// //printf("calling free with ptr = %p\n", ptr);
	new_size = 0;
	if ((header = find_header_tiny_or_small(ptr, &g_data, &new_size)))
	{
		//printf("malloc found ! at emplacement : %p\n", (void*)header + sizeof(t_header));
		if (new_size == -1)
		{
			return;
		}
		else if (new_size)
			header->size = new_size;
		header->used = 0;
	}
	else if ((index = find_header_large(ptr, g_data.large)) != -1)
	{
		// //printf("large malloc found.\n");
		if (!unmap_and_shift_page(index, g_data.large))
		{
			// //printf("unmap failed.\n");
			// perror("");
		}
	}
	else
	{
		//printf("malloc not found.\n");
	}
}

void	*malloc(size_t size)
{
	//printf ("////////////APPEL A MALLOC//////////////\n");
	// write(1, "a\n", 2);
	// //printf("size : %zu\n", size);
	if (size <= TINY)
	{
		// write(1, "1\n", 2);
		return (tiny(size, g_data.tiny));
	}
	else if (size <= SMALL)
	{
		// write(1, "2\n", 2);
		return (small(size, g_data.small));
	}
	else
	{
		// write(1, "3\n", 2);
		return (large(size, g_data.large));
	}
	return (NULL);
}

void show_alloc_mem()
{
	do_show_alloc_mem(g_data.tiny, g_data.small, g_data.large);
}
