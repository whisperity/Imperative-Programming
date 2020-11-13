#include "point.h" /* include a saját headerre, hogy ebben a fordítási egységben
                    * 'struct Point' típus értelmes legyen! */
#include <stdio.h> /* printf, scanf */

/* Implementációs fájl point.h függvényeihez. */

struct Point read_a_point(void)
{
    /* A függvény visszatérési értéke egy rekord, amely ugyanúgy egy legális
     * művelet, mintha egy közönséges beépített típust (pl. int) adnánk vissza.
     */
    struct Point p;    /* a visszatérési értéket tartalmazó változó */

    printf("\tx = ");
    scanf("%d", &p.x);  /* p 'struct Point' típusú, annak van x nevű mezője,
                         * így p.x az a konkrét mező (abban a konkrét
                         * változóban, amit most p-nek neveztünk), amely típusa
                         * int. A címét vehetjük a rekord egy adott mezőjének,
                         * a cím típusa int* lesz. */
    printf("\ty = ");
    scanf("%d", &p.y);

    return p;
}