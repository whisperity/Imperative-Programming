#ifndef MONTH_H
#define MONTH_H

#include <stdbool.h> /* bool */

enum Month
{
    /* Enum: felsorolási típus. Konstans értékeket névvel tudunk ellátni,
     * amely nevekkel a programkódban hivatkozhatunk, és így nem mágikus
     * számok jelennek meg.
     *
     * Ezek a nevek csak a kódban élnek, C-ben nem alakítható stringgé!
     *
     * Az int és az enum típus(ok!) konstansai között automatikus átjárás van.
     * Ennek hátránya, hogy ha van egy másik enumom, amiben van 5-el
     * rendelkező konstans, akkor a MÁJUS hónap és a LILA szín egyenlő lesz...
     */

    /* Az enumkonstansok nevei konvenció szerint NAGYBETŰSEK. Az enum neve
     * C-ben NEM (C#-ban, Javaban igen, C++-ban talán) képezi az enum-érték
     * vagy enum-konstans nevének részét.
     * Azaz: JANUARY, és nem "Month.JANUARY".
     */

    JANUARY = 1, /* Kezdőértéke a januárnak az 1. hónap. */
    FEBRUARY,    /* automatikusan számoz, február 2 lesz... */
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

/* Az enumokat paraméterben ugyanúgy kezeljük, mint a structok és unionok:
 * "enum Month" együtt a típusnév, az "m" a változónév.
 */

unsigned int days_in_month(enum Month m, bool is_leap_year);
const char * month_to_str(enum Month m);

#endif // MONTH_H
