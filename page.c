/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:17:32 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/12 15:13:26 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		*create_new_page(void *collec[], size_t size)
{
	int	i;

	i = 0;
	while (collec[i] && i < P_MAX)
		i++;
	if (i == P_MAX)
		return (NULL);
	collec[i] = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
		-1, 0);
	if (collec[i] == MAP_FAILED)
	{
		collec[i] = NULL;
		return (NULL);
	}
	collec[i + 1] = NULL;
	return (collec[i]);
}

static void	*there_is_space(void **ptr, size_t blocs_needed, size_t *mem,
	size_t max_size)
{
	size_t	size;

	if ((((t_header*)(*ptr))->used == 1) ||
			(!(blocs_needed - sizeof(t_header) ==
			((t_header*)(*ptr))->size)
			&& (blocs_needed > ((t_header*)(*ptr))->size)))
	{
		size = ((t_header*)(*ptr))->size + sizeof(t_header);
		(*mem) += size;
		(*ptr) += size;
	}
	else if (*mem + sizeof(t_header) + blocs_needed + sizeof(t_header)
						> max_size)
		(*mem) += sizeof(t_header) + (blocs_needed -
			((t_header*)(*ptr))->size) + sizeof(t_header);
	else
		return (*ptr);
	return (NULL);
}

void		*find_space(void *page[], size_t blocs_needed, size_t max_size)
{
	int		i;
	void	*ptr;
	size_t	mem;

	i = 0;
	while (page[i])
	{
		mem = 0;
		ptr = page[i];
		while (mem < max_size)
		{
			if (there_is_space(&ptr, blocs_needed, &mem, max_size))
				return (ptr);
		}
		i++;
	}
	return (NULL);
}
