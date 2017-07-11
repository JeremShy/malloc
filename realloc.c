/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:17:34 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/11 21:17:35 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	*shrink_allocation_lg(void *header, size_t size, size_t old_size,
	void *ptr)
{
	void	*next_header;

	((t_header*)header)->size = size;
	next_header = (char*)header + sizeof(t_header)
		+ ((t_header*)header)->size;
	((t_header*)next_header)->used = 0;
	((t_header*)next_header)->size = old_size - size - sizeof(t_header);
	return (ptr);
}

void		*realloc_large(void *header, size_t possible_size, t_data *g_data,
	size_t size)
{
	size_t	old_size;
	void	*ptr_2;
	void	*ptr;

	header = (g_data->large)[possible_size];
	ptr = (char*)header + sizeof(t_header);
	old_size = ((t_header*)header)->size;
	if (size + sizeof(t_header) < (size_t)old_size)
		return (shrink_allocation_lg(header, size, old_size, ptr));
	else
	{
		ptr_2 = malloc(size);
		if (!ptr_2)
			return (NULL);
		ft_memcpy(ptr_2, ptr, size);
		show_alloc_mem();
		unmap_and_shift_page(possible_size, g_data->large);
		return (ptr_2);
	}
}

void		*do_realloc(void *ptr, size_t size, t_data *g_data)
{
	void	*header;
	size_t	possible_size;

	if ((header = find_header_for_realloc(ptr, g_data->tiny, g_data->small,
		&possible_size)))
		return (realloc_small_tiny(ptr, size, possible_size, header));
	else if ((possible_size = find_header_large(ptr, g_data->large)) != -1)
		return (realloc_large(header, possible_size, g_data, size));
	return (NULL);
}
