/* A jelen feladatrész az előző órai megoldás folytatása, kiegészítése újabb
 * nyelvi elemekkel és programstruktúra-szervezési gondolatokkal.
 *
 *     http://repl.it/@whisperity/imp1920166-struct
 *
 * A kommentek ebben a "projektben" csak az előző megoldáshoz képesti
 * változásokat mutatják be.
 */

#include "point.h"
#include "point_pair.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_MANTRA(ElemTipus, PointerNeve, Darab) \
    ElemTipus* const PointerNeve = \
        (ElemTipus*)(malloc(sizeof(T) * (Darab)))
/* MALLOC_MANTRA(struct Point, Points, 42); */

int main(void)
{
    printf("Hány pontot fogsz adni? ");
    size_t N;
    scanf("%zu", &N);

    if (N < 2)
    {
        perror("Párokat kell generálnom, ahhoz pedig legalább 2 elem kell!");
        return 1;
    }

    struct Point* const Points = (struct Point*)malloc(sizeof(struct Point) * N);
    /*            ^~~~~
                  A pointer konstans - a pointer által mutatott érték(ek)et meg
                  szabad változtatni, de a pointert magát arrébb állítani tilos!
                  Ez nagyon jó dolog malloc() által adott pointer esetén, mert
                  a fordítóprogram hibát ad, ha a következőket próbálná az ember
                  csinálni:

                  ++Points;
                  Points = Points + 4;
                  Points = (valami teljesen más pointer)
    */
    if (!Points)
    {
        /* perror() a standard rendszerhibák ("nincs ilyen fájl", stb.)
         * lokalizált (magyar, orosz, angol, héber, stb. ami a gép aktuális
         * nyelve) kiírására szolgál, ezt eddig "hibásan" használtuk.
         *
         * Tetszőleges hibakimenetre íráshoz fprintf(stderr, ...) használatos.
         * Ugyanúgy <stdio.h>-ból jön. Működése pont, mint a printf-é:
         *     fprintf(stderr, "Érvénytelen szám: %d\n", someIntVariable);
         */
        fprintf(stderr, "Nem sikerült a memória foglalás.\n");
        return 1;
    }

    /* A feladat megoldása során a felhasználótól beolvasott értékekből számolni
     * fogunk "nagyságrendben több" darab értéket (n²).
     * Előfordulhat, hogy a felhasználó olyan sok pontot olvastatna be, hogy
     * a pontok még elférnének, de a párok már nem.
     * Ekkor felesleges beolvasni a felhasználótól, hogy utána úgyis hibát
     * kapjon az elégtelen memória miatt.
     */
    size_t NumPairs = (N * (N - 1) ) / 2; /* N pontból álló összes egyedi
                                           * ((A, B) és (B,A) ugyanaz a pár)
                                           * párok száma. */
    struct PointPair* const Pairs = (struct PointPair*)malloc(
    /*                ^~~~~ Szintén malloc, szintén const eredmény. */
        sizeof(struct PointPair) * NumPairs);

    if (!Pairs)
    {
        /* Ha nem sikerült a párok helyének lefoglalása, a jelenlegi változata
         * a feldatnak NEM végezhető el. Erről értesítjük a felhasználót,
         * majd kiszállunk.
         */
        fprintf(stderr, "Nem sikerült a memória foglalás a párokhoz!\n");
        free(Points); /* Azonban a pontok foglalása sikerült korábban, ezt
                       * fel kell szabadítani!
                       */
        return 1;
    }

    for (size_t i = 0; i < N; ++i)
    {
        printf("Kérem a(z) %zu. pontot!\n", i + 1);
        Points[i] = read_a_point();
    }

    /* Beszúrás, indexeléssel. */
    {
        /* Az eredmény tömb K-adik helyére (kezdetben az első hely) szúrjuk
         * a készített pontpárt.
         */
        size_t K = 0;

        /* Pontpárok készítésének logikája: az első pontot az összes többivel
         * párba állítjuk. A második pontot is, de azt már az elsővel párba
         * állítottuk. A harmadik pont már párban áll az első kettővel, így
         * csak a negyedikkel, stb. kell párba állítani.
         * 
         * A külső ciklus (i) adja meg, melyik pontot állítom éppen párba, a
         * belső (j) azt, hogy melyik indexűvel.
         */

        /* Meg kell gondolni, hogy K túl fog-e indexelni az eredmény tömbön.
         * A helyzet az, hogy jelenleg épp nem, mivel matekból tudjuk vagy
         * elmondták nekünk. Most pont nem, de ebben csak akkor lehetünk
         * biztosak, ha jól meggondoltuk!
         */

        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = i + 1; j < N; ++j) {
                /* Pairs[K] egy pontpár VÁLTOZÓ, a jobb oldal eredménye is egy
                 * pontpár, ezek egymásnak értékül adhatók. */
                Pairs[K] = make_pair(&Points[i], &Points[j]);
                ++K;
                /* ^ A következő lefutása a belső ciklusmagnak az eredmény tömb
                 * következő helyére fog majd beszúrni.
                 */
            }
        }
    }

    /* Beszúrás, pointerekkel. */
    {
        /* Az eredményt a 'K' pointer (1) által mutatott területre szúrjuk.
         *
         *
         * (1): Ez most egy másik K változó, mint fentebb, hiszen két külön
         * blokk a jelenlegi és a fentebbi.
         * Blokk = { és } közötti kódszöveg, ilyenek a függvények, a ciklus
         * magja, az elágazás ágai, stb. is, és lehet önállóan csak úgy nyitni
         * egy blokkot, hogy a változó nevének láthatóságát csökkentsünk!
         */
        struct PointPair* K = Pairs;
        /* Kezdetben a beszúrás helye a lefoglalt tömb első elemén található
         * változó. K nem konstans, mivel tudnunk kell léptetni. Viszont ezt,
         * és nem Pairs-t léptetjük, hogy Pairs free()-elhetősége megmaradjon
         * a program végén!
         */

        /* A ciklusok logikája ugyanaz.
         *
         * A meggondolandó dolgok arról, hogy 'K' mennyire fog eltávolodni a
         * tömb kezdőpontjától, és az utolsó beszúrásnál is még valóban az
         * általunk foglalt és kezelhető területre szúrunk be, ugyanaz.
         *
         * Most itt se történik baj.
         */

        /* Ez a ciklus itt éppen felülírja az összes korábban kiszámított
         * pontpárt, remélhetőleg ugyanazzal az értékkel.
         */

        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = i + 1; j < N; ++j) {
                /* K egy pontpárra mutató pointer, annak dereferáltja (*K) egy
                 * pontpár változó. A jobb oldal eredménye is egy pontpár,
                 * ezek egymásnak értékül adhatók. */
                *K = make_pair(&Points[i], &Points[j]);
                ++K;
                /* ^ A következő lefutása a belső ciklusmagnak az eredmény után
                 * következő valódi "struct PointPair" méretű helyre fog szúrni.
                 *
                 * Amikor egy pointerhez hozzáadunk / levonunk, akkor a
                 * megfelelő (mutatott érték típusának méretéhez illeszkedő)
                 * darab bájttal mozog arrébb a pointer.
                 *
                 * void* által "mutatott érték" void (azaz nincs típusa),
                 * melynek tehát mérete sincs, így void* -okon a léptetés
                 * művelet nem értelmezett.
                 */
            }
        }
    }

    printf("\n\n");

    /* A minimum keresés pont úgy, mint Programozás tárgyból. A minimum
     * EREDMÉNYE a *TELJES* pontpár (Min), a vizsgált minimum érték pedig annak
     * egy mezője, a distance.
     */
    struct PointPair Min;
    Min = Pairs[0];
    for (size_t k = 0; k < NumPairs; ++k)
    {
        /* Önellenőrzés gyanánt kiírom az összes kigenerált pontpárt... */
        printf("\t(%d, %d) --> (%d, %d): %f\n",
           Pairs[k].a->x, Pairs[k].a->y,
           Pairs[k].b->x, Pairs[k].b->y,
           Pairs[k].distance);

        /* Ha az éppen aktuálisan vizsgált k-adik pontpár az összes generált
         * közül egy jobb minimum, mint az eddig gondolt minimum, akkor ez
         * legyen az új minimum.
         */
        if (Pairs[k].distance < Min.distance)
            Min = Pairs[k];
    }

    /* Technikailag elvégezhető a PÁROK felszabadítása ezen a ponton, mivel a
     * minimum eredmény (Min) tartalmaz minden olyan adatot a mezőiben, ami
     * a megjelenítéséhez kell.
     */
    free(Pairs);

    /* A ciklus végére tudjuk az egész tömbből melyik a minimum. Ezt kiírjuk. */
    printf("\nAz \"első\" legközelebbi pontpár: (%d, %d) --> (%d, %d): %f\n",
           Min.a->x, Min.a->y,
           Min.b->x, Min.b->y,
           Min.distance);

    /* Mik ezek a nyilak?
     * ------------------
     * Min.a egy 'struct Point *' változó. Ennek, mivel pointer, nincs se "x",
     * se "y" adattagja. A *MUTATOTT* értéknek van, tehát dereferálnunk kell a
     * pointert:
     *
     *     *Min.a
     *
     * azonban "*Min.a.x" kódszöveget a fordítóprogram úgy fogja értelmezni,
     * hogy "vedd a Min 'a' adattagjának 'x' adattagját és ezt dereferáld", ami
     * nem az, amit mi szeretnénk, és nem is lehet, lévén az 'a' adattag egy
     * pointer.
     *
     * Helyesen zárójelezve:
     *
     *     (*Min.a).x
     *
     * Ez már valóban az 'a' pontban található 'x' koordinátát fogja megadni:
     *   1. Min.a egy pointer
     *   2. Ennek a dereferáltja egy 'struct Point'
     *   3. Ennek már van 'x' nevű adattagja/mezője.
     *
     * A fentebbi írásmódnak egy egyszerűsített változata a:
     *
     *     Min.a->x
     *
     * Ez automatikusan helyesen érti, hogy a -> *teljes* bal oldalán álló
     * dolog a pointer, amit dereferálni kell, és a dereferátumnak (mutatott
     * értének) akarjuk az 'x' mezőjét használni.
     */

    /* A lefoglalt memóriát a pontokhoz felszabadítani most CSAK a program végén
     * szabad, hiszen a Min két pontja (amely között a pár készült) nem
     * "benne él", hanem csak mutató, így ha korábban törölnénk a Points tömböt,
     * akkor a Min.a (és .b) érvénytelen területre mutatna.
     */
    free(Points);

    return 0;
}
