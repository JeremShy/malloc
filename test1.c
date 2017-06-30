#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//printf("ENTERING MAIN !!!\n");
  int i;
  char *addr;

  i = 0;
	//printf("BOUCLE !!!\n");
  while (i < 1024)
  {
   addr = (char*)malloc(1024);
   addr[0] = 42;
   i++;
  }
  return (0);
}
