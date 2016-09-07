#include <malloc.h>

void	*large(size_t size, void *large[])
{
	int	i;

	i = 0;
	printf("creating a large page...\n");
	while (large[i])
		i++;
	if (i == P_MAX)
		return (NULL);
	large[i] = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (large[i] == MAP_FAILED)
	{
		large[i] = NULL;
		printf("large page creation failed.\n");
		return (NULL);
	}
	printf("large page created at emplacement : %p\n", large[i]);
	large[i + 1] = NULL;
	return (large[i]);
}

int	find_header_large(void *ptr, void *large[])
{
	int	i;

	i = 0;
	while (large[i])
	{
		if (large[i] == ptr)
			return (i);
		i++;
	}
	return (0);
}

void	shift_large_page(int index, void *large[])
{
	
}
