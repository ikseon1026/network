#include <stdio.h>

int main(void)
{
	char a = 1;	
	char *ap = &a;
	char **app = &ap;

	int b = 1;
	int *bp = &b;
	int **bpp = &bp;

	printf("a size : %lu\n", (unsigned long)sizeof(a));
	printf("ap size : %lu\n", (unsigned long)sizeof(ap));
	printf("&a : %p\n", &a);
	printf("&ap : %p\n", &ap);
	printf("&app : %p\n", &app);
	printf("ap-1 : %p, ap : %p, ap+1 : %p\n", ap-1, ap, ap+1);
	printf("app-1 : %p, app : %p, ap+1 : %p\n", app-1, app, app+1);

	printf("b size : %lu\n", (unsigned long)sizeof(b));
	printf("bp size : %lu\n", (unsigned long)sizeof(bp));
	printf("&b : %p\n", &b);
	printf("&bp : %p\n", &bp);
	printf("&bpp : %p\n", &bpp);
	printf("bp-1 : %p, bp : %p, bp+1 : %p\n", bp-1, bp, bp+1);
	printf("bpp-1 : %p, bpp : %p,  bpp+1 : %p\n", bpp-1, bpp, bpp+1);
	
	return 0;
}				
