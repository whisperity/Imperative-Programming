#include "days.h"

#include "leapyear.h"

unsigned short days_in_year(const int year)
{
	return is_leap_year(year) ? 366 : 365;
}

unsigned long long days_lived(
	const int birth_year,
    const unsigned char birth_month,
    const unsigned char birth_day,
    const int current_year,
    const unsigned char current_month,
    const unsigned char current_day)
{
	unsigned long long days = 0;
	
	if (current_year == birth_year &&
			current_month == birth_month)
		return current_day - birth_day + 1;
	else
	{
		days += days_in_month(birth_month,
		            is_leap_year(birth_year)) - birth_day
		            + 1;
		
		int i = birth_month + 1;
		if (current_year == birth_year)
		{
			while (i < current_month)
			{
				days += days_in_month(i,
				            is_leap_year(birth_year));
				++i;
			}
			
			days += current_day;
			return days;
		}
		else
		{
			while (i <= 12)
			{
				days += days_in_month(i,
				            is_leap_year(birth_year));
				++i;
			}
			
			for (i = birth_year + 1; i <= current_year - 1; ++i)
				days += days_in_year(i);
			
			i = 1;
			while (i < current_month)
			{
				days += days_in_month(i,
				            is_leap_year(current_year));
				++i;
			}
			
			days += current_day;
			return days;
		}
	}
}
