#include "days.h"

#include "leapyear.h"

unsigned short days_in_year(const int year)
{
  switch (is_leap_year(year))
  {
    case 0:
      return 365;
    default:
      return 366;
  }

  /* return is_leap_year(year) ? 366 : 355; */
}

unsigned char days_in_month(const unsigned char month,
		                        bool leap_year)
{
  switch (month)
	{
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;

		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;

		case 2:
			return leap_year ? 29 : 28; 

		default:
			return -1;
	}
}

unsigned long long days_lived(const int birth_year,
                              const unsigned char birth_month,
                              const unsigned char birth_day,
							  const int current_year,
							  const unsigned char current_month,
							  const unsigned char current_day)
{
  unsigned long long days = 0;

	if (birth_year == current_year)
	{
		/* szuletesi ev ota nem jott uj ev, csak a honapokat kellene
		 * nezni
		 */
		if (birth_month == current_month)
		{
			/* vigyazz: ha current_day < birth_day, ez negativ, ami
			 * unsigned esetben nagyon nagy szam lesz...
			 */
			return current_day - birth_day;
		}
		else if (birth_month < current_month)
		{
			/* ebben az esetben a szuletesi honapja mar veget ert */
			days += days_in_month(birth_month, is_leap_year(birth_year))
						- birth_day;

			int i = birth_month + 1; /* a teljesen megelt honapok */
			while (i < current_month)
			{
				days += days_in_month(i, is_leap_year(birth_year));
				++i;
			}

			days += current_day;
		}
		else
			/* a szuletesi even belul kesobb szuletett mint a mai datum */
			return -1;
	}
	else if (birth_year < current_year)
	{
		/* ha volt "lezart" eve az illetonek ... */

		/* akkor a szuletesi eveben volt jobbrol lezart honapja */
		days += days_in_month(birth_month, is_leap_year(birth_year))
					- birth_day;

		int i = birth_month + 1; /* a teljesen megelt honapok a szuletesi evben */
		while (i <= 12)
		{
			days += days_in_month(i, is_leap_year(birth_year));
			++i;
		}

		/* a szuletesi ev es az aktualis ev kozott minden evet teljesen megelt */
		for (i = birth_year + 1; i <= current_year - 1; ++i)
			days += days_in_year(i);

		/* az aktualis evben vizsgalom, hogy hany honapot elt meg teljesen */
		i = 1;
		while (i < current_month)
		{
			days += days_in_month(i, is_leap_year(current_year));
			++i;
		}

		/* mar csak az hianyzik, hogy az aktualis csak balrol zart honapban hany napot elt */
		days += current_day;
	}
	else
		/* "hany ev van hatra a babaig?" szuletesi ev > aktualis ev, ez is hulyeseg */
		return -1;

	return days;
}
