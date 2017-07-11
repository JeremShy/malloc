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

void	*find_header_for_realloc(void *ptr, void *tiny[], void *small[], size_t *possible_size)
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
