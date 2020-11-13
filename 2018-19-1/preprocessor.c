#include <stdio.h>

#define PROBE 12

/*#define bool int
#define true 1
#define false 0
#define TRUE true
#define FALSE false*/

void foo(void);

int main(void)
{
	if (true == TRUE)
	{
		bool x = true;
		printf("%d\n", x);
	}
	
	printf("%d\n", PROBE);
#define PROBE 24
	printf("%d\n", PROBE);
#undef PROBE
	int PROBE = 128;
	printf("%d\n", PROBE);
	
	foo();
}



void foo(void)
{
#ifdef FOO
	printf("Foo\n");
	#if FOO > 30
		printf("%d\n", FOO);
	#else
		printf("Less than 30\n");
	#endif
#else
	printf("Noo foo :'(\n");
#endif
}
