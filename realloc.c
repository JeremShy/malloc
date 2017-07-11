#include <malloc.h>

void	*do_realloc(void *ptr, size_t size, t_data *g_data)
{
	void	*header;
	void	*next_header;
	void	*ptr_2;
	size_t		possible_size;
	size_t		old_size;

	if ((header = find_header_for_realloc(ptr, g_data->tiny, g_data->small, &possible_size)))
		return (realloc_small_tiny(ptr, size, possible_size, header));
	else if ((possible_size = find_header_large(ptr, g_data->large)) != -1)
	{
		header = (g_data->large)[possible_size];
		old_size = ((t_header*)header)->size;
		if (size + sizeof(t_header) < (size_t)old_size)
		{
			((t_header*)header)->size = size;
			next_header = header + sizeof(t_header) + ((t_header*)header)->size;
			((t_header*)next_header)->used = 0;
			((t_header*)next_header)->size = old_size - size - sizeof(t_header);
		}
		else
		{
			ptr_2 = malloc(size);
			if (!ptr_2)
				return (NULL);
			ft_memcpy(ptr_2, ptr, size);
			unmap_and_shift_page(possible_size, g_data->large);
			return (ptr_2);
		}
	}
	return (NULL);
}
