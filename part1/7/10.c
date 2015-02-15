#include <stdio.h>

struct data
{
	int a;
	struct data *next;
};

int main(void)
{
	struct data *pdata;
	struct data data1;
	struct data data2;
	struct data data3;

	data1.a = 1;
	data1.next = &data2;

	data2.a = 2;
	data2.next = &data3;

	data3.a = 3;
	data3.next = NULL;

	for(pdata=&data1; pdata; pdata = pdata->next) {
		printf("pdata.a : %d\n", pdata->a);		
		if(pdata->next)
			printf("pdata.next : %p\n", pdata->next);
	}

	return 0;
}				