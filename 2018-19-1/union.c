#include <stdio.h>

union Valami
{
  int  i;
  char c;
};

int main(void)
{
	union Valami v;
	v.i = 0xFFFFFFFF;
	printf("%d %c\n", v.i, v.c);
	v.c = '5';
	printf("%d %c\n", v.i, v.c);

	return 0;
}
