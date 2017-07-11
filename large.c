#include <malloc.h>

void	*large(size_t size, void *large[])
{
	int	i;
	int s_malloc;

	i = 0;
	while (large[i])
		i++;
	if (i == P_MAX)
		return (NULL);
	s_malloc = (sizeof(t_header) + size) % getpagesize() == 0 ?
		(sizeof(t_header) + size) : ((((sizeof(t_header) + size)
		/ getpagesize()) + 1) * getpagesize());
	large[i] = mmap(0, s_malloc, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
		-1, 0);
	if (large[i] == MAP_FAILED)
	{
		large[i] = NULL;
		return (NULL);
	}
	((t_header*)(large[i]))->size = size;
	((t_header*)(large[i]))->used = 1;
	large[i + 1] = NULL;
	return (large[i] + sizeof(t_header));
}

int		find_header_large(void *ptr, void *large[])
{
	int	i;

	i = 0;
	while (large[i])
	{
		if (large[i] + sizeof(t_header) == ptr)
			return (i);
		i++;
	}
	return (-1);
}

int		unmap_and_shift_page(int index, void *page[])
{
	if (munmap(page[index], ((t_header*)(page[index]))->size) == -1)
		return (0);
	while (page[index + 1])
	{
		page[index] = page[index + 1];
		index++;
	}
	page[index] = 0;
	return (1);
}
