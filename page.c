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
		return (NULL);
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
			if (ptr->used == 1 || (blocs_needed + sizeof(t_header) == ptr->size
				|| blocs_needed + 2 * sizeof(t_header) <= ptr->size))
			{
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
