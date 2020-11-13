/* FELADAT:
 *     1. Olvassunk be a felhasználótól egy dátum jellegű értéket (3 szám).
 *     2. Döntsük el, hogy helyes dátum-e.
 *     3. Ha igen, írjuk ki a dátumot szövegesen.
 */

#include <stdio.h> /* scanf, printf, fprintf */

#include "date/date.h"
#include "month/month.h"
#include "positional_nums/positional_nums.h"

/* Ez a struct csak a main.c-ben használatos. */
struct Date { int year; enum Month month; unsigned char day; };

struct Date read_date(void)
{
    struct Date d;
    /* Mivel az enum értékek mögötti int és az int között átjárás van,
     * olvashatom int-ként.
     */
    unsigned char month_tmp;
    scanf("%d %hhu %hhu", &d.year, &month_tmp, &d.day);
    d.month = month_tmp; /* Értékül adjuk az olvasott számot az enumnak. */
    return d;
}

int main(void)
{
    struct Date d = read_date();
    if (d.year == 0)
    {
        /* "Időszámításunkban 0" év nincs, volt -1, a következő az 1. */
        fprintf(stderr, "Érvénytelen év: 0.\n");
        return 1;
    }

    if (d.month < JANUARY || d.month > DECEMBER)
    {
        /* Mivel int-et olvastunk be (%d) egy lényegében int-be, ezért
         * simán megadhatott a felhasználó 35-öt hónapszámnak. Az enum értékei
         * nem KIZÁRÓLAGOSAN helyes értékek (C-ben, sajnos...), és nem jár se
         * fordítási, se futási hiba a hibás értékre...
         */
        /* fprintf az printf fájlba, így lehet behelyettesítős hibaüzenetet
         * is kiírni! :)
         */
        fprintf(stderr, "Érvénytelen hónap: %d\n", d.month);
        return 1;
    }

    /* Most már tudjuk, hogy az év és a hónap helyes. De mikor helyes a nap?
     * Ehhez meg kell tudnunk, hány nap van egy adott év adottadik hónapjában.
     */
    /* d.day UNSIGNED int így negatív alapból nem is lehet! A 0 helytelen,
     * és az is helytelen, ha tudjuk hogy 2382. 56. hónapja 15 napból áll,
     * akkor nem lehet 16-a.
     *
     * (A negatív inputok alulcsordulva nagyon nagy számok lesznek, ami biztos
     * nem 31, mint ahány napos hónapjaink lehetnek.)
     */
    if (d.day == 0 || d.day > days_in_month(d.month, is_leap_year(d.year)))
    {
        fprintf(stderr, "Érvénytelen nap %hhu a %d hónapban.\n",
            d.day, d.month);
        return 1;
    }

    /* ---------------------------------------------------------------------- */
    /* Most már tudjuk, hogy a felhasználó helyes dátumot adott meg. */
    printf("%d. %d. %hhu.\n", d.year, d.month, d.day);

    int year_tmp = d.year;
    /* print_positional leosztja (belül) az adottadik helyiértéken található
     * számra a számot, kiír, és visszaadja a maradékot!
     */
    year_tmp = print_positional(d.year, 4, "tízezer ");
    year_tmp = print_positional(year_tmp, 3, "ezer ");
    year_tmp = print_positional(year_tmp, 2, "száz ");
    year_tmp = print_positional(year_tmp, 1, NULL);
               print_positional(year_tmp, 0, NULL);

    printf(" %s ", month_to_str(d.month));

    /* A fenti kódban mivel print_positional() visszaadja a maradékot, ami
     * a következő print_positional hívás első paramétere, felesleges tud lenni
     * a segédváltozó, csak cserébe a kód csúnyább lesz:
     */
    /* A paraméterek kiértékelési sorrendje nem definiált az azonos
     * függvényhívás paraméterei KÖZÖTT (!), de ha az egyik paramétert egy
     * függvény állítja elő, azt muszáj TELJESEN lefuttatni, mielőtt a másik
     * függvényt futtatnánk...
     */
    print_positional(
        /* ... így tehát először a belső, tízeseket kiíró fut le, aminek
         * az eredménye a tízes maradék, vagyis az egyesek, amit kiírunk
         * később.
         */
        print_positional(d.day, 1, NULL),
        0, NULL);

    printf("\n");
    return 0;
}
