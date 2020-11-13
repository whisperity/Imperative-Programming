#include "date.h"

bool is_leap_year(int year)
{
    /* Egy év akkor szökőév, ha 4-gyel osztható és százzal nem osztható.
     * Ezen felül akkor is, ha 400-zal osztható.
     */
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
