
#include <stdio.h>
#include <stdlib.h>

#include "date.h"
#include "days.h"

int main(void)
{
  printf("Hello!\n");
  printf("What is your birth date? (in the format of YYYY. MM. DD.) ");

  struct Date birth;
  int read = scanf("%d. %d. %hhu", &birth.year, &birth.month, &birth.day);

  if (birth.month > 12 || birth.day > 31)
  {
    fprintf(stderr, "Error: Invalid month or day specified...\n");
    exit(1);
  }

  if (read != 3)
  {
    fprintf(stderr,
      "Error: supposed to fill 3 variables, but couldn't.\nInput badly formatted?\n");
    exit(1);
  }
  
  struct Date current;
  current.year = 2018; current.month = OCTOBER; current.day = 1;

  printf("You have lived %llu day(s)!\n",
    days_lived(birth, current));

  return 0;
}