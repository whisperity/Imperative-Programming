#include "days.h"

#include "leapyear.h"

unsigned short days_in_year(const int year)
{
	return is_leap_year(year) ? 366 : 365;
}

unsigned long long days_lived(
  const struct Date birth,
  const struct Date current)
{
	unsigned long long days = 0;
 	
	if (current.year == birth.year &&
			current.month == birth.month)
		return current.day - birth.day + 1;
	else
	{
		days += days_in_month(birth) - birth.day + 1;

		struct Date d = birth;
		d.month += 1;
		if (current.year == birth.year)
		{
			while (d.month < current.month)
			{
				days += days_in_month(d);
				++d.month;
			}
			
    
			days += current.day;

			return days;
		}
		else
		{
			while (d.month <= 12)
			{
				days += days_in_month(d);
				++d.month;
			}

			for (d.year = birth.year + 1;
				d.year <= current.year - 1; ++d.year)
			  days += days_in_year(d.year);
			
			d = current;
			d.month = 1;
			while (d.month < current.month)
			{
				days += days_in_month(d);
				++d.month;
			}
			
			days += current.day;
			return days;
		}
	}
}
