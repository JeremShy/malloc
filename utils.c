#include <malloc.h>

size_t get_t_psize(void)
{
	return ((100 * (sizeof(t_header) + TINY)) % getpagesize() == 0 ?
		(100 * (sizeof(t_header) + TINY)) : ((((100 * (sizeof(t_header) + TINY))
		/ 4096) + 1) * 4096));
}

size_t get_s_psize(void)
{
	return ((100 * (sizeof(t_header) + SMALL)) % getpagesize() == 0 ? \
		(100 * (sizeof(t_header) + SMALL)) : ((((100 * (sizeof(t_header) + SMALL))
		/ 4096) + 1) * 4096));
}
