#include "days.h"

#include "leapyear.h"

unsigned char days_in_month(
  const struct Date date)
{
	switch (date.month)
	{
		case JANUARY:
		case MARCH:
		case MAY:
		case JULY:
		case AUGUST:
		case OCTOBER:
		case DECEMBER:
			return 31;
		case APRIL:
		case JUNE:
		case SEPTEMBER:
		case NOVEMBER:
			return 30;
/*		case 2:
			return is_leap_year(date.year) ? 29 : 28;
		default:
			return -1;*/
	}
}
