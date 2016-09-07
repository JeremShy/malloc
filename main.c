#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	printf("size of t_header : %zu\n", sizeof(t_header));
	char *str = ft_strdup("123456791345678");
	printf("%s\n", str);
	free(str);
	return (0);
}
