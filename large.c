#include <malloc.h>

void	*large(size_t size, void *large[])
{
	int	i;

	i = 0;
	// printf("creating a large page...\n");
	while (large[i])
		i++;
	if (i == P_MAX)
		return (NULL);
	large[i] = mmap(0, sizeof(t_header) + size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (large[i] == MAP_FAILED)
	{
		large[i] = NULL;
		// printf("large page creation failed.\n");
		return (NULL);
	}
	// printf("large page created at emplacement : %p\n", large[i]);
	((t_header*)(large[i]))->size = size;
	large[i + 1] = NULL;
	return (large[i] + sizeof(t_header));
}

int	find_header_large(void *ptr, void *large[])
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

int	unmap_and_shift_large_page(int index, void *large[])
{
	if (munmap(large[index], ((t_header*)(large[index]))->size) == -1)
		return (0);
	while (large[index + 1])
	{
		large[index] = large[index + 1];
		index++;
	}
	large[index] = 0;
	return (1);
}
