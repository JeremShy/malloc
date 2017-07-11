#include <malloc.h>

static void	*divide_next_header(void *header, size_t size, size_t possible_size)
{
	void	*next_header;
	size_t	old_size;

	old_size = ((t_header*)header)->size;
	((t_header*)header)->size = size;
	next_header = header + sizeof(t_header) + ((t_header*)header)->size;
	((t_header*)next_header)->used = 0;
	((t_header*)next_header)->size = possible_size - (size - old_size);
	return (header + sizeof(t_header));
}

static void	*create_new_and_free_old(size_t size, void *ptr)
{
	void	*ptr_2;

	ptr_2 = malloc(size);
	if (!ptr_2)
		return (NULL);
	ft_memcpy(ptr_2, ptr, size);
	free(ptr);
	return (ptr_2);
}

static void	*shorten_allocation(void *header, size_t size, void *ptr)
{
	size_t	old_size;
	void	*next_header;

	old_size = ((t_header*)header)->size;
	((t_header*)header)->size = size;
	next_header = header + sizeof(t_header) + ((t_header*)header)->size;
	((t_header*)next_header)->used = 0;
	((t_header*)next_header)->size = old_size - size - sizeof(t_header);
	return (ptr);
}

void		*realloc_small_tiny(void *ptr, size_t size, size_t possible_size,
	void *header)
{
	if (possible_size != 0)
	{
		if (size == possible_size + ((t_header*)header)->size +
			sizeof(t_header))
		{
			((t_header*)header)->size = size;
			return (header + sizeof(t_header));
		}
		else if (size <= possible_size + ((t_header*)header)->size)
			return (divide_next_header(header, size, possible_size));
	}
	if (size + sizeof(t_header) > ((t_header*)header)->size)
		return (create_new_and_free_old(size, ptr));
	else
		return (shorten_allocation(header, size, ptr));
}
