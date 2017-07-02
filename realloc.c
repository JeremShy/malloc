#include <malloc.h>

static void *find_header_in_page(void *ptr, void *page, size_t p_size, int *possible_size)
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
				*possible_size = ((t_header*)next_header)->used;
			return (header);
		}
		header = header + sizeof(t_header) + ((t_header*)header)->size;
	}
	return (NULL);
}

static void	*find_header_for_realloc(void *ptr, void *tiny[], void *small[], int *possible_size)
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
	int		possible_size;
	int		old_size;

	if ((header = find_header_for_realloc(ptr, g_data->tiny, g_data->small, &possible_size)))
	{
		if (possible_size != 0)
		{
			if (size == possible_size + ((t_header*)header)->size + sizeof(t_header))
			{
				((t_header*)header)->size = size;
				return (header + sizeof(t_header));
			}
			else if (size <= possible_size + ((t_header*)header)->size)
			{
				old_size = ((t_header*)header)->size;
				((t_header*)header)->size = size;
				next_header = header + sizeof(t_header) + ((t_header*)header)->size;
				((t_header*)next_header)->used = 0;
				((t_header*)next_header)->size = possible_size - (size - old_size);
			}
		}
		if (size + sizeof(t_header) > ((t_header*)header)->size)
		{
			ptr_2 = malloc(size);
			ft_memcpy(ptr_2, ptr, size);
			free(ptr);
			return (ptr_2);
		}
		else
		{
			old_size = ((t_header*)header)->size;
			((t_header*)header)->size = size;
			next_header = header + sizeof(t_header) + ((t_header*)header)->size;
			((t_header*)next_header)->used = 0;
			((t_header*)next_header)->size = old_size - sizeof(t_header);
		}
	}

	return (NULL);
}
