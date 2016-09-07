#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	char *str = ft_strdup("penis");
	char *str2 = ft_strdup("penis2");
	char *str3 = ft_strdup("peniaaaaaaaaaaaaas2");
	printf("%s - %s- %s\n", str, str2, str3);
	return (0);
}
