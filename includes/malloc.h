/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 15:19:40 by jcamhi            #+#    #+#             */
/*   Updated: 2017/06/30 15:56:02 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define TINY 512
# define SMALL 1536
# define P_MAX 10000

# include <sys/mman.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <libft.h>

typedef struct	s_header {
	int		used;
	size_t	size;
}				t_header;

typedef struct	s_data {
	void	*tiny[P_MAX + 1];
	void	*small[P_MAX + 1];
	void	*large[P_MAX + 1];
}				t_data;

void					*malloc(size_t size);
void					free(void *ptr);
size_t				get_t_psize(void);
size_t				get_s_psize(void);
void					*create_new_page(void *collec[], size_t size);
void					*find_space(void *page[], size_t blocs_needed, size_t max_size);
void					*small(size_t size, void *small[]);
void					*tiny(size_t size, void *tiny[]);
void					*large(size_t size, void *large[]);
t_header				*find_header_tiny_or_small(void	*ptr, void *tiny[], void *small[], size_t *new_size);
int						find_header_large(void *ptr, void *large[]);
int						unmap_and_shift_large_page(int index, void *large[]);
void					do_show_alloc_mem(void *tiny[], void *small[], void *large[]);
void 					show_alloc_mem();
void 					ft_put_addr(void *addr);

#endif
