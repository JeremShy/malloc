#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	printf("!!!!!!!!!!!!!! size of t_header : %zu - %#lx !!!!!!!!!!\n", sizeof(t_header), sizeof(t_header));
	printf("!!!!!!!!!!!!!! size of t_p_size : %zu - %#lx !!!!!!!!!!!!\n", get_t_psize(), get_t_psize());

	printf("Allocating 2 * 28 bytes..\n");
	char *str = ft_strdup("123456789123456789123456789");
	char *str2 = ft_strdup("123456789123456789123456789");
	// printf("%s- %s\n", str, str2);
	// printf("BEFORE\n");
	show_alloc_mem();
	free(str);
	printf("AFTER\n");
	show_alloc_mem();

	printf("Allocating 1 * 11 bytes..\n");
	char *str3 = ft_strdup("1234567891");
	show_alloc_mem();

	str  = NULL;
	str2 = NULL;
	str3 = NULL;
	return (0);
}
