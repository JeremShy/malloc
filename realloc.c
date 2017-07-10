#include <malloc.h>

static void *find_header_in_page(void *ptr, void *page, size_t p_size, size_t *possible_size)
{
	void	*header;
	void	*eop;
	void	*next_header;

	eop = page + p_size;
	if (ptr >= eop || ptr < page)
		return (NULL);
	header = page;
	while (header < eop)
	{
		if (header + sizeof(t_header) == ptr)
		{
			next_header = header + sizeof(t_header) + ((t_header*)header)->size;
			if (next_header >= eop)
				*possible_size = 0;
			else if (((t_header*)next_header)->used == 1)
				*possible_size = 0;
			else if (((t_header*)next_header)->used == 0)
				*possible_size = ((t_header*)next_header)->size;
			return (header);
		}
		header = header + sizeof(t_header) + ((t_header*)header)->size;
	}
	return (NULL);
}

static void	*find_header_for_realloc(void *ptr, void *tiny[], void *small[], size_t *possible_size)
{
	void *ret;
	int		i;

	i = 0;
	*possible_size = 0;
	while (tiny[i])
	{
		if ((ret = find_header_in_page(ptr, tiny[i], get_t_psize(), possible_size)))
			return (ret);
		i++;
	}
	i = 0;
	while (small[i])
	{
		if ((ret = find_header_in_page(ptr, small[i], get_s_psize(), possible_size)))
			return (ret);
		i++;
	}
	return (NULL);
}

void	*do_realloc(void *ptr, size_t size, t_data *g_data)
{
	void	*header;
	void	*next_header;
	void	*ptr_2;
	size_t		possible_size;
	size_t		old_size;

	if ((header = find_header_for_realloc(ptr, g_data->tiny, g_data->small, &possible_size)))
	{
		// write(1, "0\n", 2);
		if (possible_size != 0)
		{
			// write(1, "1\n", 2);
			if (size == possible_size + ((t_header*)header)->size + sizeof(t_header))
			{
				// write(1, "2\n", 2);
				((t_header*)header)->size = size;
				return (header + sizeof(t_header));
			}
			else if (size <= possible_size + ((t_header*)header)->size)
			{
				// write(1, "3\n", 2);
				old_size = ((t_header*)header)->size;
				((t_header*)header)->size = size;
				next_header = header + sizeof(t_header) + ((t_header*)header)->size;
				((t_header*)next_header)->used = 0;
				((t_header*)next_header)->size = possible_size - (size - old_size);
				return (header + sizeof(t_header));
			}
		}
		if (size + sizeof(t_header) > ((t_header*)header)->size)
		{
			// write(1, "4\n", 2);
			ptr_2 = malloc(size);
			if (!ptr_2)
				return (NULL);
			ft_memcpy(ptr_2, ptr, size);
			free(ptr);
			return (ptr_2);
		}
		else
		{
			// write(1, "5\n", 2);
			old_size = ((t_header*)header)->size;
			((t_header*)header)->size = size;
			next_header = header + sizeof(t_header) + ((t_header*)header)->size;
			((t_header*)next_header)->used = 0;
			((t_header*)next_header)->size = old_size - sizeof(t_header);
		}
	}
	else if ((possible_size = find_header_large(ptr, g_data->large)) != -1)
	{
		// write(1, "6\n", 2);
		header = (g_data->large)[possible_size];
		old_size = ((t_header*)header)->size;
		if (size + sizeof(t_header) < (size_t)old_size)
		{
			// write(1, "7\n", 2);
			((t_header*)header)->size = size;
			next_header = header + sizeof(t_header) + ((t_header*)header)->size;
			((t_header*)next_header)->used = 0;
			((t_header*)next_header)->size = old_size - size - sizeof(t_header);
		}
		else
		{
			// write(1, "8\n", 2);
			ptr_2 = malloc(size);
			if (!ptr_2)
				return (NULL);
			ft_memcpy(ptr_2, ptr, size);
			unmap_and_shift_page(possible_size, g_data->large);
			return (ptr_2);
		}
	}
	// write(1, "9\n", 2);
	return (NULL);
}
