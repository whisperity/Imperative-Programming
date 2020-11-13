#include "positional_nums.h"

#include <math.h> /* pow, kell -lm fordításkor! */
#include <stdio.h> /* printf, fprintf, stderr */
#include <stdlib.h> /* exit */

static int print_positional_tens(int num)
{
    if (num == 0)
        /* Ha nullát akarnánk kiírni (tizensokként), nem írunk ki semmit. */
        return 0;
    if (num >= 100)
    {
        fprintf(stderr,
            "érvénytelen tízesszám kiírás %d, ez nem legfeljebb 100!", num);
        exit(1);
        /* exit kinyítja a programot. */
    }

    int last_digit = num % 10;

    switch (num / 10)
        /* Például 2008 / 1000. Mivel egész osztás, a számjegyet kapjuk meg. */
    {
        case 1:
            /* A case belsejében tetszőlegesen komplex kód lehet, amíg nem
             * akarunk lokális változót létrehozni, az ugyanis nem fog menni,
             * kivéve, ha nyitunk egy blokkot.
             */

            if (last_digit == 0)
                printf("tíz");
            else
                printf("tizen");
            break;
        case 2:
            if (last_digit == 0)
                printf("húsz");
            else
                printf("huszon");
            break;
        case 3: printf("harminc"); break;
        case 4: printf("negyven"); break;
        case 5: printf("ötven"); break;
        case 6: printf("hatvan"); break;
        case 7: printf("hétven"); break;
        case 8: printf("nyolcvan"); break;
        case 9: printf("kilencven"); break;

        case 0:
        default:
            /* Ha az osztás eredménye 0 egésszer a tíz, akkor nem írunk ki
             * semmit.
             */
            break;
    }

    /* Visszatérünk a helyiérték rész levágás utáni maradékkal, ezt korábban
     * kiszámoltuk.
     */
    return last_digit;
}

int print_positional(int num, int pow_of_10, const char * suffix)
{
    if (pow_of_10 == 1)
        /* A tízesek kiírása a ragozás miatt speciális, egy helyi (kívülről
         * nem látszik, mivel nem része a headernek, és nem hívható, mivel
         * statikus függvény!) segédfüggvény oldja meg.
         */
        return print_positional_tens(num);

    /* A számjegyek helyiértékes kiírásához először meghatározzuk a
     * paraméterben kapott helyiértéken lévő számot.
     */
    int power = pow(10, pow_of_10);
    switch (num / power)
    /* Például 2008 / 1000. Mivel egész osztás, a számjegyet kapjuk meg. */
    {
        case 1:
            if (!suffix)
                /* Az 1 esetén csak akkor írjuk ki, hogy "egy", ha NINCS
                 * suffix... Azaz "egy" kijön, de az "egyezer" csak "ezer"
                 * lesz.
                 */
                printf("egy");
            break;
        case 2: printf("kettő"); break;
        case 3: printf("három"); break;
        case 4: printf("négy"); break;
        case 5: printf("öt"); break;
        case 6: printf("hat"); break;
        case 7: printf("hét"); break;
        case 8: printf("nyolc"); break;
        case 9: printf("kilenc"); break;

        case 0:
        default:
            /* Ha az osztás eredménye 0 egésszer a tízhatvány, akkor
             * nem írjuk ki, ha a felhasználó ki akarta írni, hogy "ezer",
             * például.
             */
            suffix = NULL;
            break;
    }

    if (suffix)
    {
        /* Ha a felhasználó megkért minket, hogy kiírjunk egy hatványt jelölő
         * szót, és nem 0 volt korábban (mert akkor NULL-ra állt a pointer!),
         * akkor kiírjuk.
         */
        printf("%s", suffix);
    }

    /* Visszatérünk a helyiérték rész levágás utáni maradékkal, pl. 2008 ezresei
     * után azzal, hogy 8. 993 szásai után azzal, hogy 93, stb.
     */
    return num % power;
}
