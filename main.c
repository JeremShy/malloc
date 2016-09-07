#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	printf("size of t_header : %zu\n", sizeof(t_header));
	// char *str = ft_strdup("penis");
	char *pouet = malloc(0);
	// printf("%s\n", str);
	free(pouet);
	return (0);
}
