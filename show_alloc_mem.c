#include <malloc.h>

void	do_show_alloc_mem(t_data g_data)
{
	(void)g_data;

	ft_putstr("TINY : ");
	ft_put_addr(g_data.tiny);
	printf("[%p]\n", g_data.tiny);
}
