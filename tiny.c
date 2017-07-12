/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:17:44 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/12 15:18:02 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	*create_page_ti(size_t *ancient_size, void *tiny[])
{
	void	*page;

	page = create_new_page(tiny, get_t_psize());
	if (!page)
		return (NULL);
	*ancient_size = get_t_psize() - sizeof(t_header);
	return (page);
}

static void	create_header(void *page, size_t ancient_size, size_t size,
	int header_creation)
{
	if (header_creation && ancient_size != size)
	{
		page = ((t_header*)page)->size + page + sizeof(t_header);
		((t_header*)page)->size = ancient_size - sizeof(t_header) - size;
		((t_header*)page)->used = 0;
	}
}

void		*tiny(size_t size, void *tiny[])
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
		if (!(page = create_page_ti(&ancient_size, tiny)))
			return (NULL);
	}
	else
	{
		if (((t_header*)page)->size == size + sizeof(t_header))
			header_creation = 0;
		ancient_size = header_creation ? ((t_header*)page)->size : 0;
	}
	((t_header*)page)->size = size;
	((t_header*)page)->used = 1;
	ret = page + sizeof(t_header);
	create_header(page, ancient_size, size, header_creation);
	return (ret);
}
