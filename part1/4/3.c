#include <stdio.h>

int main(void)
{
	printf("char : %lu\n", (unsigned long)sizeof(char));	
	printf("short :%lu\n", (unsigned long)sizeof(short));
	printf("int : %lu\n", (unsigned long)sizeof(int));	
	printf("long : %lu\n", (unsigned long)sizeof(long));
	printf("float : %lu\n", (unsigned long)sizeof(float));
	printf("double : %lu\n", (unsigned long)sizeof(double));

	printf("char * : %lu\n", (unsigned long)sizeof(char*));	
	printf("short * : %lu\n", (unsigned long)sizeof(short*));
	printf("int * : %lu\n", (unsigned long)sizeof(int*));	
	printf("long * : %lu\n", (unsigned long)sizeof(long*));
	printf("float * : %lu\n", (unsigned long)sizeof(float*));
	printf("double * : %lu\n", (unsigned long)sizeof(double*));

	return 0;
}				
