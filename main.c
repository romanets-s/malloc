#include "malloc.h"
#include <stdio.h>


int main()
{
	void *ptr;

	ptr = malloc(1);
	printf("%p\n", ptr);
}