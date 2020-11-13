#include <stdio.h>

#define FOO 43

int main(void)
{
#if FOO == 42
  printf("Hello, World! %d\n", FOO);
#else
  printf("Banyek.\n");
#endif
  return 0;
}