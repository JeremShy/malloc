#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	int	i;
	char *str1;
	(void)ac;
	(void)av;

	printf("!!!!!!!!!!!!!! size of t_header : %zu - %#lx !!!!!!!!!!\n", sizeof(t_header), sizeof(t_header));
	printf("!!!!!!!!!!!!!! size of t_p_size : %zu - %#lx !!!!!!!!!!!!\n", get_t_psize(), get_t_psize());
	printf("Allocating 2 * 10 bytes..\n");
	i = 0;
	while (i < 102)
	{
		str1 = ft_strdup("123456789");
		return (0);
		// char *str2 = ft_strdup("123456789");
		i++;
	}
	// printf("%s- %s\n", str, str2);
	// printf("BEFORE\n");
	show_alloc_mem();
	// free(str1);
	// show_alloc_mem();
  // free(NULL);
	// printf("AFTER\n");
	// show_alloc_mem();
	// return (0);
	//
	// printf("Allocating 1 * 11 bytes..\n");
	// char *str3 = ft_strdup("1234567890");
	// show_alloc_mem();
	//
	str1  = NULL;
	// str2 = NULL;
	// str3 = NULL;
	return (0);
}
