#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	int	i;
	char *str1;
	char *str2;
	(void)ac;
	(void)av;

	//printf("!!!!!!!!!!!!!! size of t_header : %zu - %#lx !!!!!!!!!!\n", sizeof(t_header), sizeof(t_header));
	//printf("!!!!!!!!!!!!!! size of t_p_size : %zu - %#lx !!!!!!!!!!!!\n", get_t_psize(), get_t_psize());
	// //printf("Allocating 2 * 10 bytes..\n");
	i = 0;
	// show_alloc_mem();
	//printf("------------------------------------------\n");
	// while (i < 10)
	// {
	// 	str1 = malloc(0);
	// 	show_alloc_mem();
	// 	// free(str1);
	// 	// show_alloc_mem();
	// 	i++;
	// }
	str1 = malloc(50);
	show_alloc_mem();
	str1[49] = '\0';
	str1 = realloc(str1, 60);
	show_alloc_mem();
	str1[59] = '\0';
	free(str1);
	show_alloc_mem();
	//printf("------------------------------------------\n");

	// char *str2 = ft_strdup("1234567");
	// show_alloc_mem();
	// //printf("------------------------------------------\n");
	//
	// char *str3 = ft_strdup("1234567");
	// show_alloc_mem();
	// //printf("------------------------------------------\n");
	//
	// char *str4 = ft_strdup("1234567");
	// show_alloc_mem();
	// //printf("//////////////////////////////////////////\n");

	// free(str2);
	// show_alloc_mem();
	// //printf("//////////////////////////////////////////\n");
	//
	// free(str1);
	// show_alloc_mem();
	//printf("//////////////////////////////////////////\n");

	// free(str3);
	// show_alloc_mem();
	//printf("//////////////////////////////////////////\n");


	// free(str4);
	// show_alloc_mem();
	//printf("//////////////////////////////////////////\n");
	// while (i < 10)
	// {
	// 	str1 = ft_strdup("1234567");
	// 	free(str1);
	// 	// return (0);
	// 	// char *str2 = ft_strdup("123456789");
	// 	i++;
	// }
	//printf("BEFORE\n");
	// show_alloc_mem();
	// free(str1);
	// show_alloc_mem();
  // free(NULL);
	//printf("AFTER\n");
	// show_alloc_mem();
	// return (0);
	//
	//printf("Allocating 1 * 11 bytes..\n");
	// char *str3 = ft_strdup("1234567890");
	// show_alloc_mem();
	//
	str1  = NULL;
	// str2 = NULL;
	// str3 = NULL;
	//printf("!!!!!!!!!!!!!! size of t_header : %zu - %#lx !!!!!!!!!!\n", sizeof(t_header), sizeof(t_header));
	return (0);
}

// #include <strings.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define M (1024 * 1024)
//
// void print(char *s)
// {
//   write(1, s, strlen(s));
// }

// int main()
// {
//   char *addr1;
//   char *addr3;
//
//   addr1 = (char*)malloc(16*M);
//   strcpy(addr1, "Bonjours\n");
//   print(addr1);
// 	show_alloc_mem();
//   addr3 = (char*)realloc(addr1, 17*M);
// 	show_alloc_mem();
//   addr3[17*M - 1] = 42;
//   print(addr3);
//   return (0);
// }
