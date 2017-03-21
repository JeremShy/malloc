#include <malloc.h>

void	*tiny(size_t size, void *tiny[])
{
	int		blocs_needed;
	void	*page;
	int		header_creation; // À 1 si il faut creer un header apres la nouvelle zone.
	size_t	ancient_size;
	void	*ret;

	blocs_needed = sizeof(t_header) + size;
	printf("blocs needed : %d - %#x\n", blocs_needed, blocs_needed);
	header_creation = 1;
	if (!(page = find_space(tiny, blocs_needed, get_t_psize())))
	{
		printf("Creating a new tiny page..\n");
		page = create_new_page(tiny, get_t_psize());
		if (!page)
			return (NULL);
		printf("tiny page created at emplacement : %p\n", page);
		ancient_size = get_t_psize();
	}
	else
	{
		printf("tiny zone found at emplacement : %p\n", page);
		if (((t_header*)page)->size == blocs_needed + sizeof(t_header))
			header_creation = 0;
		else
			ancient_size = ((t_header*)page)->size;
	}
	((t_header*)page)->size = size;
	((t_header*)page)->used = 1;
	printf("size : %#lx\n", ((t_header*)page)->size);
	printf("page : %p\n", page);
	printf("debut (apres header): %p, fin : %p\n", page + sizeof(t_header), page + sizeof(t_header) + size);
	ret = page + sizeof(t_header);
	if (header_creation)
	{
		printf("creating a new header after the new zone. (Ancient size : %#lx)\n", ancient_size);
		page = page + sizeof(t_header) + ((t_header*)page)->size;
		((t_header*)page)->size = ancient_size - sizeof(t_header) - size;
		((t_header*)page)->used = 0;
		printf("New header size : %#zx (%zu bytes)\n", ((t_header*)page)->size, ((t_header*)page)->size);
	}
	printf("returning %p\n", ret);
	return (ret);
}
