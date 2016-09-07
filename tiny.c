#include <malloc.h>

void	*tiny(size_t size, void *tiny[])
{
	int		blocs_needed;
	void	*page;
	int		header_creation;
	size_t	ancient_size;
	void	*ret;

	blocs_needed = sizeof(t_header) + size;
	header_creation = 1;
	if (!(page = find_space(tiny, blocs_needed, get_t_psize())))
	{
		// printf("Creating a new tiny page..\n");
		page = create_new_page(tiny, blocs_needed);
		if (!page)
			return (NULL);
		// printf("tiny page created at emplacement : %p\n", page);
		ancient_size = get_t_psize();
	}
	else
	{
		// printf("tiny zone found at emplacement : %p\n", page);
		if (((t_header*)page)->size == blocs_needed + sizeof(t_header))
			header_creation = 0;
		else
			ancient_size = ((t_header*)page)->size;
	}
	((t_header*)page)->size = size;
	((t_header*)page)->used = 1;
	ret = page + sizeof(t_header);
	if (header_creation)
	{
		page = ((t_header*)page)->size + page + sizeof(t_header);
		((t_header*)page)->size = ancient_size - sizeof(t_header) * 2 - size;
		((t_header*)page)->used = 0;
	}
	return (ret);
}
