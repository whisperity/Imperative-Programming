#include <stdio.h>

int a(void);
int b(void);
int c(void);
int d(void);

int main(int argc, char** argv)
{
	int (*funptr[])(void) = { &a, &b, &c, &d };
	
	char c;
	printf("Input? ");
	scanf("%c", &c);
	
	/*switch (c)
	{
		case 'a':
			return a();
			break;
		case 'b':
			return b();
			break;
		...
	}
	*/
	
	int X = funptr[c - 'a']();
	printf("Result is %d\n", X);
	return X;
}

int a(void) { return 2; }

int b(void) { return 4; }

int c(void) { return 6; }

int d(void) { return 8; }
