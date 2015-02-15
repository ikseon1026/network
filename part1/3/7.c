#include <stdio.h>

enum day {MON, TUE, WED, THU, FRI, SAT, SUN};
enum test {A = 100, B = 103, C}; 

int main(void)
{
	enum day d;

	d = MON;

	printf("MON : %d, TUE : %d, WED :%d, THU : %d, "\
			"FRI : %d, SAT : %d, SUN : %d \n", 
		MON, TUE, WED, THU, FRI, SAT, SUN);

	printf("A : %d, B : %d, C : %d\n", A, B, C);

	switch(d)
	{
		case MON:
			printf("hello! world!\n");
			break;
		case TUE:
			break;
		case WED:
			break;
		case THU:
			break;
		case FRI:
			break;
		case SAT:
			break;
		case SUN:
			break;
	}
	
	return 0;
}				
