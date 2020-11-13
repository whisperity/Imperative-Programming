#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int leap_year(const int year);
int prime(const int num);

int main(void)
{
	int year;
	printf("What is your birth year? ");
	scanf("%d", &year);
	
	printf("Your birth year is: %d.\n", year);
	
	if (leap_year(year))
	{
		printf("It is a leap year. Cannot be a prime! :)\n");
	}
	else
	{
		printf("It is not a leap year.\n");
		/* printf("But is it a prime? %d\n", prime(year)); */
		/* a ? b : c */
		printf("Is it a prime number? %s\n",
			prime(year) ? "Yes it is! :)" : "No, it is not.");
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
	else if (year % 400 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int prime(const int num)
{
	if (num < 0)
	{
		fprintf(stderr, "Error: negative numbers cannot be primes.\n");
		exit(1);
	}
	else if (num == 0 || num == 1)
	{
		return 0;
	}
	else
	{
		for (int probe = 2; probe <= sqrt(num); ++probe)
			if (num % probe == 0)
				return 0;
		
		return 1;
	}
}
