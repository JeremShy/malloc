#include <malloc.h>
#include <errno.h>

void	*create_new_page(void *collec[], size_t size)
{
	int	i;

	i = 0;
	while (collec[i] && i < P_MAX)
		i++;
	if (i == P_MAX)
		return (NULL);
	printf("size : %zu\n", size);
	collec[i] = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (collec[i] == MAP_FAILED)
	{
		collec[i] = NULL;
		return (NULL);
	}
	collec[i + 1] = NULL;
	return (collec[i]);
}

void	*find_space(void *page[], size_t blocs_needed, size_t max_size)
{
	int	i;
	t_header *ptr;
	size_t		mem;

	i = 0;
	while (page[i])
	{
		mem = 0;
		ptr = (t_header*)page[i];
		while (mem < max_size)
		{
			printf("boucle : ptr = %p\n", ptr);
			// if (ptr->used == 1 || (blocs_needed + sizeof(t_header) == ptr->size
			// 	|| blocs_needed + 2 * sizeof(t_header) <= ptr->size))
			if ((ptr->used == 1) ||
				(!(blocs_needed == ptr->size) && (blocs_needed + sizeof(t_header) > ptr->size)))
			{
				printf("on incremente ptr\n");
				mem += ptr->size + sizeof(ptr);
				ptr += ptr->size + sizeof(ptr);
			}
			else
				return (ptr);
		}
		i++;
	}
	return (NULL);
}

static	t_header	*find_header_in_page(void	*ptr, void *page, size_t page_max)
{
	void	*header;
	void	*end_of_page;

	header = page;
	end_of_page = header + page_max;
	printf("page + header = %p\n", page + sizeof(t_header));
	printf("%p\n", ptr);
	while (header < end_of_page)
	{
		if (header + sizeof(t_header) == ptr)
			return (ptr);
		header = header + ((t_header*)(header))->size + sizeof(t_header);
	}
	return (NULL);
}

t_header	*find_header_tiny_or_small(void	*ptr, void *tiny[], void *small[])
{
	int				i;
	t_header	*header;

	i = 0;
	while (tiny[i])
	{
		if ((header = find_header_in_page(ptr, tiny[i], get_t_psize())))
			return (header);
		i++;
	}
	i = 0;
	while (small[i])
	{
		if ((header = find_header_in_page(ptr, small[i], get_s_psize())))
			return (header);
		i++;
	}
	return (NULL);
}
