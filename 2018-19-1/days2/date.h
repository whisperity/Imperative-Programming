#ifndef DATE_H
#define DATE_H

enum Month
{
  JANUARY = 1,
  FEBRUARY = 2,
  MARCH = 3,
  APRIL = 4,
  MAY = 5,
  JUNE = 6,
  JULY = 7,
  AUGUST = 8,
  SEPTEMBER = 9,
  OCTOBER = 10,
  NOVEMBER = 11,
  DECEMBER = 12
};

struct Date
{
  int year;
  enum Month month;
  unsigned char day;
};


#endif /* DATE_H */