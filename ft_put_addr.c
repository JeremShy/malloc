#include <malloc.h>

static int	compte(unsigned long nbr, int base)
{
	int ret;

	ret = 0;
	while (nbr != 0)
	{
		nbr /= base;
		ret++;
	}
	return (ret);
}

char	get_char_for_tab(int *i)
{
	(*i)++;
	if (((*i) - 1) < 10)
		return (((*i) - 1) + '0');
	else if (((*i) - 1) < 17)
		return (((*i) - 1) - 10 + 'a');
	else
		return ('\0');
}

void ft_put_addr(void *addr)
{
	char					tab[17];
	int						i;
	unsigned long	nbr;
	char					tabl[40];
	int						nb;

	i = 0;
	nbr = (unsigned long)addr;
	ft_putstr("0x");
	while (i <= 17)
		tab[i - 1] = get_char_for_tab(&i);
	i = 1;
	nb = compte(nbr, 16);
	while (nbr != 0)
	{
		tabl[nb - i] = tab[nbr % 16];
		nbr /= 16;
		i++;
	}
	tabl[nb] = '\0';
	ft_putstr(tabl);
}
