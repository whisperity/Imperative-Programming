#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* printf("Hello World\n"); */
/* int x = 5;
x += 43;
*/

/*
Igaza'bo'l lehetne ilyet is tru"kko"zni. :)
#define bool int
#define true 1
#define false 0
#define TRUE true
#define FALSE false
*/

int leap_year(const int year);
unsigned long long number_of_divisors(const int num);
int prime(const int num);

int main(void)
{
  int year;

  printf("Your birth year is? ");
  scanf("%d", &year);
  
  printf("Your birth year is %d.\n", year);
  
  if (leap_year(year))
  {
    printf("It is a leap year! ;)\n");
  }
  else
  {
    printf("It is not a leap year :(.\n");
    /* printf("But is it a prime number? %d\n", prime(year)); */
    printf("%s\n", prime(year) ? "It is a prime number!"
                               : "Not a prime...");
  }
  
  return 0;
}

int leap_year(const int year)
{
  /* if (!(year % 4) && year % 100) */
  if (year % 4 == 0 && year % 100 != 0)
  {
    return 1;
  }
  /* else if (!(year % 400)) */
  else if (year % 400 == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

unsigned long long number_of_divisors(const int num)
{
  if (num < 0)
  {
    fprintf(stderr, "Error: we didn't define divisibility "
                    "on negative numbers.\n");
    exit(1);
    return -1;
  }
  else if (num == 0 || num == 1)
    return 1;
  else
  {
    unsigned long long divisors = 2;

    for (int probe = 2; probe < num; ++probe)
    {
      if (num % probe == 0)
        ++divisors;
    }
    
    return divisors;
  }
}

int prime(const int num)
{
  /*
  if (num < 0)
  {
    fprintf(stderr, "Error: negative numbers cannot be primes.\n");
    exit(1);
    return -1;
  }
  else if (num == 0 || num == 1)
    return 0;
  else
  {
    for (int probe = 2; probe <= sqrt((double)num); ++probe)
    {
      if (num % probe == 0)
        return 0;
    }
    
    return 1;
  }
  */
  return number_of_divisors(num) == 2;  
}