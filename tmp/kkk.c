# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>



int main()
{
	int i = 100;
	while (i--)
		printf("%d\n", i);
	printf("________________________\n");
	i = 100;
	//while(--i)
	//	printf("%d\n", i);
}