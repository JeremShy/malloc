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

char	get_char_for_tab(int *i) // Mais si c'est clair..
{
	(*i)++;
	if (((*i) - 1) < 10)
		return (((*i) - 1) + '0');
	else if (((*i) - 1) < 17)
		return (((*i) - 1) - 10 + 'a');
	else
		return ('\0');
}

void ft_put_addr(void *addr) // Fonction sensée afficher une addresse sans avoir besoin de malloc(3). Simplement, elle affiche l'adresse
{                            // A l'envers, ce qui est assez génant.
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

// char		*ft_itoa_base(unsigned int nbr, int base)
// {
// 	char		*retour;
// 	int			nb;
// 	int			i;
// 	char		tab[17];
//
// 	if (nbr == 0)
// 		return (ft_alloc_str("0"));
// 	ft_strcpy(tab, "0123456789abcdef");
// 	nb = compte(nbr, base);
// 	retour = mallocp(nb + 1);
// 	i = 1;
// 	while (nbr != 0)
// 	{
// 		retour[nb - i] = tab[nbr % base];
// 		nbr /= base;
// 		i++;
// 	}
// 	retour[nb] = '\0';
// 	return (retour);
// }
