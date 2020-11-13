#include <stdio.h>
#include <stdlib.h>

#define SIZE ((unsigned long long)2 << 21)
/* #define SIZE ((unsigned long long)2 << 22) */

#define SIZE_MASIK ((unsigned long long)2 << 27)

void my_bad_alloc()
{
  int* p = (int*)malloc(sizeof(int) * SIZE_MASIK);
  for (size_t i = 0; i < SIZE_MASIK; ++i)
	p[i] = i;

  return;
}

int main(void)
{
  printf("%llu\n", SIZE);
  int x = 0;
  char tomb[SIZE];
  
  printf("%p %p %p\n", &x, &tomb[0], &tomb[SIZE - 1]);
  
  printf("Please press ENTER\n");
  scanf("%d", &x);
  
  int* tomb2 = (int*)malloc(sizeof(int) * SIZE_MASIK);
  
  if (tomb2 == NULL)
  {
    fprintf(stderr, "No alloc :(\n");
    exit(1);
  }
  
  printf("%p %p\n", &tomb2[0], &tomb2[SIZE_MASIK - 1]);
  
  printf("Please press ENTER\n");
  scanf("%d", &x);
  
  tomb2[0] = 0;
  *(tomb2 + 1) = 1;
  tomb2[SIZE_MASIK - 1] = 42;
  
  printf("Please press ENTER\n");
  scanf("%d", &x);
  
  my_bad_alloc();
  my_bad_alloc();
  my_bad_alloc();
  my_bad_alloc();
  
  printf("Please press ENTER\n");
  scanf("%d", &x);
  
  for (size_t i = 0; i < SIZE_MASIK; ++i)
	tomb2[i] = i;
  
  printf("Please press ENTER\n");
  scanf("%d", &x);
  
  free(tomb2);
  
  printf("Please press ENTER\n");
  scanf("%d", &x);
  
  return 0;
}
