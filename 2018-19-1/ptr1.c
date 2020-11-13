#include <stdio.h>

int main(void)
{
  int x = 4;
  x = 15;
  
  printf("%d\n", x);
  
  int* p = &x;
  
  printf("%p\n", p);
  printf("%d\n", *p);
  
  const int y = 42;
  printf("%d\n", y);
  
  const int *p2 = &y;
  /* *p2 = 420; */
  printf("%d\n", *p2);
  p2 = &x;
  printf("%d %d\n", y, *p2);
  
  int * const p3 = &x;
  printf("%d\n", *p3);
  *p3 = 128;
  printf("%p %d %d %p %d\n", p3, *p3, x, p, *p);
  
  /* p3 = 0xDEADBEEF; */
  const int * const p4 = &y;
  /* p4 = &x;
  *p4 = x; */
  
  const int * const * p5 = &p4;
  
  printf("&p: %p\n", &p);
  printf("&p2: %p\n", &p2);
  printf("&p3: %p\n", &p3);
  printf("&p4: %p\n", &p4);
  printf(" p5: %p\n", p5);
  printf("&p5: %p\n", &p5);
  
  /* std::shared_ptr<T>
  std::shared_ptr<const T>
  const std::shared_ptr<T>
  const std::shared_ptr<const T> */
  
  
  
  
  return x;
}
