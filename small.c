#include <malloc.h>

void	*small(size_t size, void *small[])
{
	int		blocs_needed;
	void	*page;
	int		header_creation;
	size_t	ancient_size;
	void	*ret;

	blocs_needed = sizeof(t_header) + size;
	header_creation = 1;
	if (!(page = find_space(small, blocs_needed, get_s_psize())))
	{
		//printf("Creating a new small page..\n");
		page = create_new_page(small, get_s_psize());
		if (!page)
		{
			//printf("error\n");
			return (NULL);
		}
		// //printf("small page created at emplacement : %p\n", page);
		ancient_size = get_s_psize();
	}
	else
	{
		// //printf("small zone found at emplacement : %p\n", page);
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
	//printf("returning alloc small %p\n", ret);
	return (ret);
}
