/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 15:31:57 by jcamhi            #+#    #+#             */
/*   Updated: 2016/09/07 18:25:27 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_data	g_data = {.tiny[0] = NULL, .small[0] = NULL, .large[0] = NULL};

void	*malloc(size_t size)
{
	// printf ("////////////APPEL A MALLOC//////////////\n");
	if (size <= TINY)
		return (tiny(size, g_data.tiny));
	else if (size <= SMALL)
		return (small(size, g_data.small));
	else
		return (large(size, g_data.large));
	// printf("Tiny : %d, t_header : %zu, 100 allocs : %zu\n", TINY, sizeof(t_header), 100 * (TINY + sizeof(t_header)));
	// printf("small : %d, t_header : %zu, 100 allocs : %zu\n", SMALL, sizeof(t_header), 100 * (SMALL + sizeof(t_header)));
	// printf("taille : %zu et %zu\n", get_t_psize(), get_s_psize());
	return (NULL);
}
