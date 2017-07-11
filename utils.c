/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:17:46 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/11 21:17:52 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t	get_t_psize(void)
{
	return ((100 * (sizeof(t_header) + TINY)) % getpagesize() == 0 ?
		(100 * (sizeof(t_header) + TINY)) : ((((100 * (sizeof(t_header) + TINY))
		/ getpagesize()) + 1) * getpagesize()));
}

size_t	get_s_psize(void)
{
	return ((100 * (sizeof(t_header) + SMALL)) % getpagesize() == 0 ? \
		(100 * (sizeof(t_header) + SMALL)) :
		((((100 * (sizeof(t_header) + SMALL))
		/ getpagesize()) + 1) * getpagesize()));
}
