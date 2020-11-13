#include "point_pair.h"
#include <math.h>

struct PointPair make_pair(struct Point* a, struct Point* b)
{
    struct PointPair pp;

    /* Itt most beállítom, hogy a létrehozott pontpár mutatói arra a két
     * pontra mutassanak, amelyekkel létrehoztuk azt.
     */
    pp.a = a;
    pp.b = b;


    /* (Nyilak magyarázata main.c alján!) */
    pp.distance = sqrt(
        pow( pp.a->x - pp.b->x, 2 )
        +
        pow( pp.a->y - pp.b->y, 2 )
    );

    return pp;
}
