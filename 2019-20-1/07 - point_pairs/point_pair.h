#ifndef POINT_PAIR_H
#define POINT_PAIR_H

#include "point.h"

struct PointPair
{
    /* Mivel a pontokat a felhasználótól valahová beolvastuk már, megtehetjük
     * (tervezési döntés kérdése!), hogy a párokban nem tároljuk el újra és
     * újra ugyanazt a pontot a hozzá párosított párok létrehozása során,
     * hanem az eredeti, a memóriában valahol létező 'struct Point' példányra
     * mutató mutatót helyezünk el.
     * 
     * Ez azért jó, mert ha 'struct Point' kellően nagy, akkor spórolunk a
     * memóriával, és előfordulhat, hogy esetleg a párba állított pontok
     * tulajdonságai változnak menet közben (pl. színezés, súlyozás, név
     * rendelődik hozzájuk, ilyen tulajdonságok és tételek lesznek majd matek
     * vagy algoritmusok tárgyból!), amely módosulása esetén a pontpár
     * "irányából" is látnunk kell jól a változást.
     * 
     * Ha a pont "belemásolódik" a párba, akkor onnantól kezdve ezt a
     * "központi módosítás" lehetőségét elveszítettük!
     * 
     * Vigyázzunk azonban, a pointerezés egyrészt drága tud lenni (lévén a
     * processzornak el kell ugornia a memóriában máshova!), másrészt
     * elszúrható!
     */
    struct Point* a;
    struct Point* b;

    double distance;
};

/* Mivel a pontokba most már pointereket teszünk, a beolvasásnál is a párt
 * alkotó mutatókat kell átvennünk.
 */
struct PointPair make_pair(struct Point* a, struct Point* b);

#endif // POINT_PAIR_H
