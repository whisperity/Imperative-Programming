#ifndef POINT_PAIR_H
#define POINT_PAIR_H

#include "point.h"    /* A pontpár típus csak akkor értelmes, ha a pont típus
                       * értelmes, így először be kell includeolni a másik
                       * headert. Mivel a további headertől való függést
                       * feloldó include-olást csak akkor kell elvégezni,
                       * amikor a header először includeolódik, így ez a
                       * #include a header guardon BELÜLRE kerül.
                       */

struct PointPair
{
    struct Point a; /* Rekord mezője lehet bármely addigra definiált (ismert)
                     * típus, így másik rekord, pointer, tömb, bármi.
                     */
    struct Point b;

    double distance;
};
/* A pontpár két pontból, és a köztük húzott egyenes távolságából áll. */

/* Összerakunk a paraméterben kapott két pontot egy párrá. Ez a függvény
 * kiszámolja a két pont távolságát is. */
struct PointPair make_pair(struct Point a, struct Point b);

#endif // POINT_PAIR_H