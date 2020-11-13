#include <stdbool.h>

unsigned short days_in_year(const int year);
unsigned char days_in_month(const unsigned char month,
		                    bool leap_year);

unsigned long long days_lived(const int birth_year,
                              const unsigned char birth_month,
                              const unsigned char birth_day,
							  const int current_year,
							  const unsigned char current_month,
						      const unsigned char current_day);

