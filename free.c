/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:16:55 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/11 21:16:55 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static t_header		*first_if(t_header *header, int *new_size)
{
	void	*next_header;
	void	*nnheader;

	next_header = (char*)header + sizeof(t_header) + ((t_header*)header)->size;
	nnheader = (char*)next_header + sizeof(t_header) +
		((t_header*)next_header)->size;
	if (((t_header*)next_header)->used == 0)
		*new_size = ((t_header*)header)->size + sizeof(t_header)
			+ ((t_header*)next_header)->size;
	return (header);
}

static t_header		*second_if(t_header *header, t_header *next_header,
	int *new_size)
{
	void	*nnheader;

	nnheader = (char*)next_header + sizeof(t_header)
		+ ((t_header*)next_header)->size;
	if (((t_header*)header)->used == 0)
	{
		if (((t_header*)nnheader)->used == 0)
			*new_size = ((t_header*)header)->size + sizeof(t_header) +
				((t_header*)next_header)->size + sizeof(t_header)
				+ ((t_header*)nnheader)->size;
		else
			*new_size = ((t_header*)header)->size + sizeof(t_header)
				+ ((t_header*)next_header)->size;
		return (header);
	}
	if (((t_header*)nnheader)->used == 0)
		*new_size = ((t_header*)next_header)->size + sizeof(t_header)
			+ ((t_header*)nnheader)->size;
	return (next_header);
}

static	t_header	*find_header_for_free(void *ptr, void *page,
	size_t page_max, int *new_size)
{
	void	*header;
	void	*eop;
	void	*next_header;

	header = page;
	eop = page + page_max;
	*new_size = 0;
	if (ptr >= eop || ptr < page)
		return (NULL);
	if (header + sizeof(t_header) == ptr)
		return (first_if(header, new_size));
	while (header < eop)
	{
		next_header = header + sizeof(t_header) + ((t_header*)header)->size;
		if (next_header >= eop)
			return (NULL);
		if (next_header + sizeof(t_header) == ptr &&
			((t_header*)next_header)->used)
			return (second_if(header, next_header, new_size));
		header = next_header;
	}
	return (NULL);
}

t_header			*find_header_tiny_or_small(void *ptr, t_data *pages,
		int *new_size)
{
	int			i;
	t_header	*header;
	void		**tiny;
	void		**small;

	tiny = pages->tiny;
	small = pages->small;
	i = 0;
	while (tiny[i])
	{
		if ((header = find_header_for_free(ptr, tiny[i], get_t_psize(),
			new_size)))
			return (header);
		i++;
	}
	i = 0;
	while (small[i])
	{
		if ((header = find_header_for_free(ptr, small[i], get_s_psize(),
			new_size)))
			return (header);
		i++;
	}
	return (NULL);
}
