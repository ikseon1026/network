#include <stdio.h>

struct a
{
	int a1;
	int a2;
};

struct b
{
	int b1;
	int b2;
};

struct data
{
	struct a a;
	struct b b;
};

int main(void)
{
	struct data data;

	struct data *pdata = &data;
	struct a *ap = &(data.a);
	struct b *bp = &(data.b);

	data.a.a1 = 1;
	data.a.a2 = 2;
	data.b.b1 = 3;
	data.b.b2 = 4;

	printf("ap->a1 : %d, ap->a2 : %d\n", ap->a1, ap->a2);
	printf("bp->b1 : %d, bp->b2 : %d\n", bp->b1, bp->b2);

	printf("pdata->a.a1 : %d, pdata->a.a2 : %d\n", pdata->a.a1, pdata->a.a2);
	printf("pdata->b.b1 : %d, pdata->b.b2 : %d\n", pdata->b.b1, pdata->b.b2);
	
	return 0;
}				
