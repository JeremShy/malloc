/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:17:37 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/11 21:17:41 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void				*print_area(void *ptr, int *tot)
{
	if (((t_header*)ptr)->used == 1)
	{
		ft_put_addr(ptr + sizeof(t_header));
		ft_putstr(" - ");
		ft_put_addr(ptr + sizeof(t_header) + ((t_header*)ptr)->size);
		ft_putstr(" : ");
		ft_putnbr(((t_header*)ptr)->size);
		if (((t_header*)ptr)->used == 1)
			ft_putstr(" octets\n");
		else
			ft_putstr(" octets. (Not allocated)\n");
		*tot += ((t_header*)(ptr))->size;
	}
	ptr = ptr + sizeof(t_header) + (size_t)(((t_header*)ptr)->size);
	return (ptr);
}

static unsigned long	print_page_content(void *page[], size_t page_max,
		char *str)
{
	int				tot;
	void			*ptr;
	size_t			end_of_page;
	int				i;

	i = 0;
	tot = 0;
	while (page[i])
	{
		ft_putstr(str);
		ft_put_addr(page[i]);
		ft_putchar('\n');
		ptr = (t_header*)page[i];
		end_of_page = (size_t)ptr + page_max;
		while ((size_t)ptr < end_of_page)
			ptr = print_area(ptr, &tot);
		i++;
	}
	return (tot);
}

static unsigned long	print_large_pages(void *page[])
{
	int		tot;
	void	*ptr;
	int		i;

	i = 0;
	tot = 0;
	while (page[i])
	{
		ft_putstr("LARGE :");
		ft_put_addr(page[i]);
		ft_putchar('\n');
		ptr = (t_header*)page[i];
		if (((t_header*)ptr)->used == 1)
		{
			ft_put_addr(ptr + sizeof(t_header));
			ft_putstr(" - ");
			ft_put_addr(ptr + sizeof(t_header) + ((t_header*)ptr)->size);
			ft_putstr(" : ");
			ft_putnbr(((t_header*)ptr)->size);
			ft_putstr(" octets\n");
			tot += ((t_header*)(ptr))->size;
		}
		i++;
	}
	return (tot);
}

void					do_show_alloc_mem(void *tiny[],
		void *small[], void *large[])
{
	int	tot;

	(void)large;
	tot = print_page_content(tiny, get_t_psize(), "TINY : ");
	tot += print_page_content(small, get_s_psize(), "SMALL : ");
	tot += print_large_pages(large);
	ft_putstr("Total : ");
	ft_putnbr(tot);
	ft_putstr(" octets\n");
}
