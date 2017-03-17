#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	printf("!!!!!!!!!!!!!! size of t_header : %zu - %#lx !!!!!!!!!!\n", sizeof(t_header), sizeof(t_header));

	char *str = ft_strdup("123456789");
	char *str2 = ft_strdup("123456789");
	// printf("%s- %s\n", str, str2);
	// printf("BEFORE\n");
	// show_alloc_mem();
	str = NULL;
	str2 = NULL;
	// free(str);
	// printf("AFTER\n");
	// show_alloc_mem();
	return (0);
}
