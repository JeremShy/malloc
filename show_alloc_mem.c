#include <malloc.h>

static unsigned long	print_page_content(void *page[], size_t page_max, char *str)
{
	int		tot;
	t_header	*ptr;
	size_t		end_of_page;
	int		i;

	i = 0;
	tot = 0;
	while (page[tot])
	{
		ft_putstr(str);
		ft_put_addr(page[tot]);
		ft_putchar('\n');
		ptr = (t_header*)page[tot];
		end_of_page = (size_t)ptr + page_max;
		while ((size_t)ptr < end_of_page)
		{
			ft_put_addr(ptr + sizeof(t_header));
			ft_putstr(" - ");
			ft_put_addr(ptr + sizeof(t_header) + ptr->size);
			ft_putstr(" : ");
			ft_putnbr(ptr->size);
			ft_putstr(" octets\n");
			tot += ptr->size;
			ptr = ptr + sizeof(t_header) + ptr->size;
		}
		tot++;
	}
	return (tot);
}

void	do_show_alloc_mem(void *tiny[], void *small[], void *large[])
{
	int	tot;

	(void)large;
	tot = print_page_content(tiny, get_t_psize(), "TINY : ");
	tot += print_page_content(small, get_s_psize(), "SMALL : ");
	ft_putstr("Total : ");
	ft_putnbr(tot);
	ft_putstr(" octets\n");
}
