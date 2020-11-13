#include "point_pair.h" /* Ebben a fordítási egységben a PointPair és a Point is
                         * értelmes (definiált) kell legyen, így be kell húznunk
                         * mindkét releváns headert. Szerencsére a "pontpárnak"
                         * kell a "pont" jelentése, így ide egy #include-dal
                         * megússzuk.
                         */
#include <math.h> /* sqrt, pow */
/* Mivel speciális matematikai függvényeket használunk a math.h-ból, ezért
 * bármilyen binárist is kívánunk készíteni ezen fordítási egység
 * felhasználásával, ahhoz hozzá kell majd linkelni a matematikai függvények
 * implementációs könyvtárát, különben "undefined reference"-t kapunk:
 * 
 * Ehhez az '-l' kapcsolót használjuk (jelentése: dinamikus alkalmazáskönyvtár
 * linkelése). Az alkalmazáskönyvtár neve "m", a valódi implementáció valahol a
 * rendszeren telepítve szerepel (/usr/lib/... általában), ahonnan a linker
 * meg fogja találni:
 * 
 *     gcc -c pointpair.c -o pointpair.o
 *     gcc -c main.c -o main.o
 *     gcc pointpair.o main.o -lm -o pointpairs
 * 
 *                            ^~~
 */

struct PointPair make_pair(struct Point a, struct Point b)
{
    struct PointPair pp; /* Hasonlóan kell egy változó amivel visszatérünk... */

    /* A pontpár két pontból áll. A pontpár mezői a párt alkotó pontok, így
     * azoknak a változóknak **is** értéket kell adnunk, hogy a pontpár rekord
     * minden mezője értelmes (nem memóriaszemét) adatot tartalmazzon.
     */
    pp.a = a; /* Ahogy két int értékül adható egymásnak, úgy két 'struct Point'
               * is. Ez az értékadás a struct összes mezőjét egyesével értékül
               * adja a jobb oldalból a bal oldalnak. Ez az értékadás egy
               * másolásként fogható fel, jelen esetben pp.a.x -be kerül a.x
               * értéke, y-ba y, és b-re ugyanez.
               */
    pp.b = b;

    /* Két pont ((x₁, y₁) és (x₂, y₂)) távolsága Euklideszi
     * koordinátarendszerben:
     *     √( (x₁ - x₂)² + (y₁ - y₂)² )
     */
    double xD = (pp.a.x - pp.b.x); /* x₁ és x₂ távolsága */
    double yD = (pp.a.y - pp.b.y); /* y₁ és y₂ távolsága */
    xD = pow(xD, 2); /* négyzetre emelés */
    yD = pow(yD, 2);
    pp.distance = sqrt(xD + yD); /* a négyzetösszegek gyöke */

    /* Egy kifejezésként ugyanez: */
    pp.distance = sqrt( pow( pp.a.x - pp.b.x, 2 ) + pow( pp.a.y - pp.b.y, 2) );
    /*                       ^~~~~~                      ^~~~~~
     *                       pp pontpárnak van a mezője, így 'pp.a' az egyik
     *                       pont a párban. Ez viszont szintén egy rekord típus,
     *                       amelynek további mezői vannak, x és y.
     */

    return pp;
}
