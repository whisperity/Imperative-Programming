#ifndef DAYS_H
#define DAYS_H

#include <stdbool.h>

#include "date.h"

unsigned short days_in_year(
  const int year);

unsigned char days_in_month(
  const struct Date date);

unsigned long long days_lived(
  const struct Date birth,
  const struct Date current);

#endif /* DAYS_H */