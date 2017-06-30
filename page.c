#include <malloc.h>void	*create_new_page(void *collec[], size_t size){	int	i;	i = 0;	while (collec[i] && i < P_MAX)		i++;	if (i == P_MAX)		return (NULL);	//printf("size : %zu\n", size);	collec[i] = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);	if (collec[i] == MAP_FAILED)	{		collec[i] = NULL;		return (NULL);	}	ft_bzero(collec[i], size);	collec[i + 1] = NULL;	return (collec[i]);}void	*find_space(void *page[], size_t blocs_needed, size_t max_size){	int	i;	void	*ptr;	size_t		mem;	size_t	size;	i = 0;	while (page[i])	{		mem = 0;		ptr = page[i];		while (mem < max_size)		{			// //printf("boucle : ptr = %p\n", ptr);			// if (ptr->used == 1 || (blocs_needed + sizeof(t_header) == ptr->size			// 	|| blocs_needed + 2 * sizeof(t_header) <= ptr->size))			if ((((t_header*)ptr)->used == 1) ||				(!(blocs_needed - sizeof(t_header) == ((t_header*)ptr)->size) && (blocs_needed > ((t_header*)ptr)->size)))			{				size = ((t_header*)ptr)->size + sizeof(t_header);				// //printf("on incremente ptr. ptr : %p, ptr->size : %#lx. On ajoute : %#lx\n", ptr, ((t_header*)ptr)->size, size);				mem += size;				ptr += size;			}			else if (mem + sizeof(t_header) + blocs_needed + sizeof(t_header) > max_size)			{				mem += sizeof(t_header) + (blocs_needed - ((t_header*)ptr)->size) + sizeof(t_header);			}			else			{				//printf("On retourne de find_space: %p\n", ptr);				//printf("blocks_needed: %zu - %#lx\nptr->size %zu - %#lx\n", blocs_needed, blocs_needed, ((t_header*)ptr)->size, ((t_header*)ptr)->size);				return (ptr);			}		}		i++;	}	return (NULL);}// static	t_header	*find_header_in_page(void	*ptr, void *page, size_t page_max, size_t *new_size)// {// 	void	*header;// 	void	*end_of_page;// 	void  *ret;// 	void	*next_header;// 	void	*next_2_header;//// 	header = page;// 	end_of_page = header + page_max;// 	ret = header;// 	*new_size = 0;// 	while (header < end_of_page)// 	{// 		//printf ("header :  %p\n, end_of_page : %p, size : %zu\n", header, end_of_page, ((t_header*)header)->size);// 		// !!! TODO :  Attention aux sefaults si on est au dernier ou à l'avant dernier header de la page.// 		if ((header + ((t_header*)header)->size + sizeof(t_header) * 2) == ptr// 				&& ((t_header*)(header + sizeof(t_header) + ((t_header*)header)->size))->used)// 		{// 			write(1, "b\n", 2);// 			next_header = header + sizeof(t_header) + ((t_header*)header)->size;// 			//printf("1\n");// 			ret = next_header;// 			if (!((t_header*)header)->used)// 			{// 				ret = header;// 				*new_size = ((t_header*)header)->size + sizeof(t_header) + ((t_header*)next_header)->size;// 			}// 			next_2_header = next_header + sizeof(t_header) + ((t_header*)next_header)->size;// 			if (((t_header*)(next_2_header))->used == 0)// 				*new_size = *new_size + sizeof(t_header) + ((t_header*)(next_2_header))->size;// 			return (ret);// 		}// 		else if (header + sizeof(t_header) == ptr && ((t_header*)header)->used)// 		{// 			write(1, "c\n", 2);// 			next_header = header + sizeof(t_header) + ((t_header*)header)->size;// 			if (((t_header*)(next_header))->used == 0)// 				*new_size = *new_size + sizeof(t_header) + ((t_header*)(next_header))->size;// 			return (header);// 		}// 		header = header + ((t_header*)(header))->size + sizeof(t_header);// 	}// 	return (NULL);// }static	t_header	*find_header_in_page(void	*ptr, void *page, size_t page_max, size_t *new_size) {	void	*header = page;	void	*eop = page + page_max;	void	*next_header;	void	*nnheader;	*new_size = 0;	if (ptr >= eop)		return (NULL);	if (header + sizeof(t_header) == ptr)	{		next_header = header + sizeof(t_header) + ((t_header*)header)->size;		next_header = next_header + sizeof(t_header) + ((t_header*)header)->size;		if (((t_header*)next_header)->used == 0)		{			*new_size = ((t_header*)header)->size + sizeof(t_header) + ((t_header*)next_header)->size;		}		//printf("returning %p (1)\n", header);		return (header);	}	while (header < eop)	{		next_header = header + sizeof(t_header) + ((t_header*)header)->size;		if (next_header >= eop)		{			//printf("returning NULL (1)\n");			return (NULL);		}		if (next_header + sizeof(t_header) == ptr)		{			nnheader = next_header + sizeof(t_header) + ((t_header*)next_header)->size;			if (((t_header*)header)->used == 0)			{				if (((t_header*)nnheader)->used == 0)				{					*new_size = ((t_header*)header)->size + sizeof(t_header) + ((t_header*)next_header)->size + sizeof(t_header) + ((t_header*)nnheader)->size;				}				else				{					*new_size = ((t_header*)header)->size + sizeof(t_header) + ((t_header*)next_header)->size;				}				//printf("returning %p (2)\n", header);				return (header);			}			if (((t_header*)nnheader)->used == 0)			{				*new_size = ((t_header*)next_header)->size + sizeof(t_header) + ((t_header*)nnheader)->size;			}			//printf("returning %p (3)\n", next_header);			return (next_header);		}		else		{			//printf("Error : %p != %p\n", next_header + sizeof(t_header), ptr);		}		header = next_header;	}	//printf("returning NULL (2)\n");	return (NULL);}t_header	*find_header_tiny_or_small(void	*ptr, void *tiny[], void *small[], size_t *new_size){	int				i;	t_header    	*header;	i = 0;	while (tiny[i])	{		if ((header = find_header_in_page(ptr, tiny[i], get_t_psize(), new_size)))			return (header);		i++;	}	i = 0;	while (small[i])	{		if ((header = find_header_in_page(ptr, small[i], get_s_psize(), new_size)))			return (header);		i++;	}	return (NULL);}