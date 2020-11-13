#include <stdio.h>
#include <stdlib.h>  /* malloc() és free() az stdlib.h-ban van. */

/* A dinamikus memóriakezelés során lehetőségünk nyílik:
 *  - memóriaterületek felhasználói bementtől/környezettől függő méretével
 *    történő foglalására.
 *  - a lefoglalt memóriaterület élettartamának testreszabott kezelésére.
 * 
 * A legfoglalt memória a program által használt memóriaterület "heap"-nek
 * nevezett részében jön létre. Arra nincs garancia, hogy a lefoglalt terület
 * fizikailag hol lesz, az egyetlen garancia, hogy *összefüggő* (mint a tömbök)
 * területet kapunk.
 * 
 * A VLA ("int T[n];") problémája, hogy élete a definiáló függvény
 * területére korlátozódik (mint bármely lokális változó), viszont ha 'n'
 * (elemszám) kellően nagy, akkor Stack Overflow hiba (általában Segmentation
 * fault kíséretében) keletkezik, amit nem lehet a programon belül lekezelni,
 * míg a malloc() sikertelenség esetén NULL-lal tér vissza, amelyet értelmesen
 * kezelhetünk.
 */

int main(void)
{
    /* FELADAT: Kérdezzük meg a felhasználót, mennyi számot szeretne megadni,
     * majd olvassunk be annyi darab, de 0-nál szigorúan nagyobb (!) számot!
     *
     * Ezeket tároljuk egy dinamikus memóriakezeléssel allokált tömbben.
     */
   
    /* Felhasználói inputtól függ a méret, megkérdezzük a felhasználót. */
    /* size_t: előjel nélküli szám amely ábrázolni képes a legnagyobb lehetséges
     * méretet. A sizeof(...) kifejezések eredménye size_t típusú. A valódi
     * jelentése a size_t-nek az adott platformtól függ, Linux környezetben 
     * általában 'long' vagy 'long long'. Tömbök indexelésekor, memória
     * foglaláskor érdemes ezt a típust használni.
     * 
     * size_t beolvasásakor/kiírásakor a "varázs" formázó karaktersorozat:
     * "%zu". u, mivel unsigned, azaz előjel nélküli, a z-t pedig a
     * fordítóprogram a megfelelő méretre (semmi, l, vagy ll) fogja cserélni.
     */

    printf("Hány számot fogsz adni? ");
    size_t N;
    scanf("%zu", &N);

    if (N < 1)
    {
        /* 0 darab elem foglalása esetén a következő sorban "sizeof(T) * 0"
         * szerepelne, ami 0. A malloc(0) hívás eredménye NEM DEFINIÁLT !!!,
         * ezért kerüljük, ha a felhasználó 0-t adott meg, akkor "elszállunk"
         * egy értelmes hibaüzenettel.
         * 
         * Negatív számú elem foglalása értelmetlen, és mivel size_t előjel
         * nélküli, ezért '(size_t)(-1)' valójában egy nagyon nagy szám...
         */
        perror("Pozitív sok hosszú tömböt kellene...\n");
        return 1;
    }

    /* void* malloc(size_t size); -- lefoglal size BÁJT (sizeof(char)) méretű
     * összefüggő területet, és visszaad egy pointert a terület első elemére.
     * Ha nem sikerül a lefoglalás, NULL pointert kapunk.
     * 
     * A terület INICIALIZÁLATLAN, pont mint a lokális változók esetén, ezért
     * csak úgy szabad olvasni mögüle, ha már írtunk oda valamit.
     * Ellenkező esetben memóriaszemét olvasódik.
     *
     * A malloc idiomatikus hívása az alábbiak szerint:
     *     T* p = (T*)malloc(sizeof(T) * N);
     * ahol T a lefoglalandó elem típusa, N pedig a darabszám.
     * 
     * (Egy elemet is lehet foglalni, akkor N értéke 1, vagy nem írjuk ki a
     * szorzást.) A sizeof(T) azért kell, mert malloc a BÁJTOK számát, és nem
     * az ELEMEK számát kéri. **1** darab T annyi bájtot foglal, amennyit a
     * sizeof(T) eredményül ad - ez egy fordítási idejű kifejezés, nem függvény
     * hívás.
     * 
     * A kapott pointert ELVESZÍTENI nem szabad, ha elveszítődik az érték
     * free-elés nélkül, akkor "MEMORY LEAK" (memóriaszivárgás) következik be.
     * 
     * A pointer gyakorlatilag "elállítható", (pl. ++T -vel), de a free() előtt
     * vissza kell állítani, lásd a fájl alján.
     * Ajánlott azonban ezt a pointert nem elállítani, inkább egy másik
     * pointert felvenni, ami ugyaninnen indul, és azt léptetni.
     * 
     * A malloc() által visszaadott pointer void* (típustalan/ismeretlen típusra
     * mutató ptr) típusú, ezt kasztoljuk (típuskikényszerítést végzünk) arra
     * a típusra, amelyként a területet használni szeretnénk.
     */
    unsigned int* T = (unsigned int*)malloc(sizeof(unsigned int) * N);
    if (!T)
    {
        /* Bármikor megtörténhet, hogy a foglalás nem sikerül, ekkor NULL
         * pointert kapunk eredményül. Ezért ellenőrizni kell MINDIG, hogy a
         * foglalás sikerült-e, és ha nem, akkor valami értelmeset csinálni.
         * 
         * if (!T) akkor igaz (akkor fut le az if ága), ha T NULL pointer volt.
         * Ellenkező esetben hamis.
         * (Hosszabban írható az if úgy is, hogy if (T == NULL)...)
         * 
         * Hogy mi az értelmes, az a konkrét feladattól függ. Ennél a példánál
         * értelmes az, hogy ezt közöljük a felhasználóval, és nem futunk
         * tovább.
         */
        perror("Nem sikerült ekkora tömböt foglalnom. Sorry :(\n");
        return 1;
    }

    /* Most, hogy sikerült lefoglalni a memória területet, elvégezzük a
     * feladatot. A tényleges feladat szempontjából innentől nem releváns, (*)
     * hogy a foglalás az malloc-kal történt, vagy statikus tömb, vagy bármi.
     */
    for (size_t i = 0; i < N; ++i)
    {
        unsigned int num;
        printf("Kérem számot %zu helyre (ne legyen 0): ", i + 1);
        scanf("%u", &num);

        if (num == 0)
        {
            /* Ebben a feladatban hiba, ha nullát szeretnénk beolvasni. Azonban
             * nem léphetünk csak úgy ki a return-nel a programból, mert volt
             * egy dinamikusan allokált terület, amelyet fel kell szabadítani.
             */
            perror("A megadott szám ne legyen nulla!");
            free(T); /* (*): az egyetlen kivétel a for() előtti állítás alól. */
            return 2;
        }

        T[i] = num;
    }

    /* Miután beolvastuk a tömböt, szépen egyesével kiírjuk a számokat.
     * Itt már tényleg egyáltalán nem látszik csak a ciklus kódjából, hogy T
     * malloc-olva lett.
     */
    for (size_t i = 0; i < N; ++i)
    {
        printf("%u ", T[i]);
    }
    printf("\n");

    /* A program vége előtt, lévén most jutottunk el oda, hogy nincs szükségünk
     * a memóriaterületre, a free() függvénnyel felszabadítjuk a memóriát,
     * visszaadjuk azt az operációs rendszernek.
     * 
     * free()-elni CSAK ÉS KIZÁRÓLAG olyan pointert szabad, amelyet a malloc()
     * függvénycsalád (malloc, calloc, realloc) adott vissza.
     * Egy konkrét pointert free()-elni KIZÁRÓLAG EGYSZER szabad.
     * 
     * (Amennyiben ezek a szabályok nem kerülnek betartásra, a program
     * viselkedése nem definiált, és bármi(!) bekövetkezhet. Legtöbb esetben
     * a végrehajtó keretrendszer/operációs rendszer azonnal kinyírja a
     * programot, amikor a "double free" (kétszer free-eljük ugyanazt a
     * területet) bekövetkezne.)
     * 
     * A free()-elés után a pointer által mutatott adatterületre a programnak
     * többet nincs joga nyúlni, az ott található adatok elvesztek, se olvasni,
     * se írni nem szabad.
     * 
     * (A pointer elállítható viszont egy másik címre, ekkor már nem fog memory
     * leak bekövetkezni.)
     */
    free(T);
    
    return 0;
}
