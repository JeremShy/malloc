/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 15:19:40 by jcamhi            #+#    #+#             */
/*   Updated: 2016/09/06 17:54:37 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define TINY 10
# define SMALL 100
# define LARGE 1000

# include <sys/mman.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_header {
	int		used;
	size_t	size;
}				t_header;

void			*malloc(size_t size);

#endif
