#include "malloc.h"
#include <stdio.h>


int main()
{
	void *ptr;

	ptr = malloc(42);
	printf("%p\n", ptr);
}