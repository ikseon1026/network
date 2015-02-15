#include <stdio.h>

int main(void)
{
	char a[] = {'h','e','l','l','o'};	
	char *p = a;	

	printf("a[n] : %c %c %c %c %c\n", a[0],a[1],a[2],a[3],a[4]);
	printf("a+n : %p, %p, %p, %p, %p\n", a+0,a+1,a+2,a+3,a+4);
	printf("*(a+n) : %c %c %c %c %c\n", *(a+0), *(a+1), *(a+2),*(a+3),*(a+4));

	printf("p[n] :%c %c %c %c %c\n", p[0],p[1],p[2],p[3],p[4]);
	printf("p+n : %p, %p, %p, %p, %p\n", p+0,p+1,p+2,p+3,p+4);
	printf("*(p+n) : %c %c %c %c %c\n", *(p+0), *(p+1), *(p+2),*(p+3),*(p+4));

	return 0;
}				
