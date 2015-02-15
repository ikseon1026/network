#include <stdio.h>

int main(void)
{
	int a[2][3] = {{1,2,3},{4,5,6}};

	printf("int : %lu\n", (unsigned long)sizeof(int));

	printf("a : %lu, (a : %p), (a + 1 : %p)\n",
		(unsigned long)sizeof(a),a,a+1);
	printf("a[0] : %lu (a[0] : %p), (a[0] + 1 : %p)\n",
		(unsigned long)sizeof(a[0]),a[0],a[0]+1);
	printf("a[0][0] : %lu (a[0][0] : %p), (a[0][0] + 1 : %p)\n",
		(unsigned long)sizeof(a[0][0]),&a[0][0],&a[0][0]+1);
	
	return 0;
}				
