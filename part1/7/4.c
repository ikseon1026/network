#include <stdio.h>

struct data 
{
	const char *s1;
	char s2[10];
};

int main(void)
{
	struct data a = {"hello", "world"};
	struct data *p;

	p = &a;

	printf("a.s1 : %s [%p], a.s2 : %s [%p]\n", a.s1, a.s1, a.s2, a.s2);
	printf("p->s1 : %s [%p], p->s2 : %s [%p]\n", p->s1, p->s1, p->s2, p->s2);

	return 0;
}				