#include <malloc.h>

size_t get_t_psize(void) // Retourne la taille d'une page tiny.
{
	return ((100 * (sizeof(t_header) + TINY)) % getpagesize() == 0 ?
		(100 * (sizeof(t_header) + TINY)) : ((((100 * (sizeof(t_header) + TINY))
		/ getpagesize()) + 1) * getpagesize()));
}

size_t get_s_psize(void) // Retourne la taille d'une page small.
{
	return ((100 * (sizeof(t_header) + SMALL)) % getpagesize() == 0 ? \
		(100 * (sizeof(t_header) + SMALL)) : ((((100 * (sizeof(t_header) + SMALL))
		/ getpagesize()) + 1) * getpagesize()));
}
