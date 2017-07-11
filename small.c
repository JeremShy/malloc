/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:17:43 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/11 21:17:44 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	*create_page_sm(size_t *ancient_size, void *small[])
{
	void	*page;

	page = create_new_page(small, get_s_psize());
	if (!page)
		return (NULL);
	*ancient_size = get_s_psize() - sizeof(t_header);
	return (page);
}

static void	create_header(void *page, size_t ancient_size, size_t size,
	int header_creation)
{
	if (header_creation)
	{
		page = ((t_header*)page)->size + page + sizeof(t_header);
		((t_header*)page)->size = ancient_size - sizeof(t_header) - size;
		((t_header*)page)->used = 0;
	}
}

void		*small(size_t size, void *small[])
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
		if (!(page = create_page_sm(&ancient_size, small)))
			return (NULL);
	}
	else
	{
		if (((t_header*)page)->size == blocs_needed + sizeof(t_header))
			header_creation = 0;
		ancient_size = header_creation ? ((t_header*)page)->size : 0;
	}
	((t_header*)page)->size = size;
	((t_header*)page)->used = 1;
	ret = page + sizeof(t_header);
	create_header(page, ancient_size, size, header_creation);
	return (ret);
}
