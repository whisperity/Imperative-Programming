#include <stdio.h>

int main(int argc, char** argv)
{
  /* ----- FELADAT: Írjunk ki egyesével minden parancssori argumentumot ----- */

  /* Amennyiben szükség van a parancssori argumentumokra, a main-nek azt a
   * "változatát" kell használni, amely átvesz egy (int, char**) paraméterezést,
   * ilyen sorrendben. (A main-nek több helyes változata van, ez az egyetlen
   * függvény, amely a C nyelv környezetében rendelkezik ezzel a
   * tulajdonsággal.)
   */

  /* A program meghívásakor (pl: $ ./echo egy ketto harom) a parancssori
   * argumentumokat a végrehajtó rendszer előkészíti az argc, argv
   * paraméterekbe.
   *
   * argc: ARGument Count -- az indításkor megadott argumentumok száma
   * argv: ARGument Vector -- a parancssori argumentumokat SZÖVEGESEN
   *       ("stringek").
   *       Igazából `argv` egy tömb (írhattuk volna 'char* argv[]' alakban is),
   *       melynek elemei mutatók (pointerek). A konkrét stringek valahol
   *       máshol élnek a memóriában, amiket ezeken a mutatókon keresztül
   *       érünk el.
   *
   *       Ennek a tömbnek a hosszát nem ismerjük fordítási időben (lévén a
   *       valóságban a mérete minden program meghívásnál más és más lehet),
   *       így valahonnan tudnunk kell a hosszát.
   *       C-ben a tömbök nem ismerik a saját hosszukat, ha paraméterként
   *       érkeznek, ezért van szükség egy külön változóra (argc), amely
   *       megmondja, hogy aktuálisan mennyi eleme van argv-nek.
   *       Ez egy darabszám!
   */
  /* Útravaló: Amikor függvényben tömböt veszünk át, mindig egy másik
   * paraméterben át kell vennünk a hosszát is!
   */

  /* Poénból írjuk ki hány darab argumentum van. */
  printf("Arg count: %d \n", argc);

  /* A tömbök iterációjának (bejárásának) klasszikus módszere egy úgynevezett
   * "számlálós" ciklus.
   *
   * A számlálós (for) ciklusnak van egy kezdeti (definíciós) értékadása, amely
   * a cikluváltozót létrehozza (definiálja) és beállítja valamilyen ismert
   * kezdeti értékre.
   *
   * A második rész a ciklusbanmaradási feltétel. Ez minden ciklusmag lefutás
   * ELŐTT megvizsgálásra kerül (az első lefutás előtt is!). Ha a feltétel
   * igazra értékelhető ki, akkor lefut a ciklusmag.
   *
   * A ciklusmag lefutása UTÁN végrehajtódik a "léptetési" utasítás. Jelenleg
   * ez 1-gyel növeli a ciklusváltozót.
   *
   * A ciklusmagban a ciklusváltozó közönséges változóként használható, akár
   * módosítható is.
   */
  for (int i = 0; i < argc; ++i)
  /*   ~~~~~~~~~
   *   ^ kezdeti értékadás
   *              ~~~~~~~~
   *              ^ feltétel
   *                        ~~~
   *                        ^ léptetési utasítás
   */
  {
    /* Jelenleg a ciklusmagban csak annyit teszünk, hogy kiírjuk az argumentum
     * számát (felhasználóbarát módon, 1-től számozva, de a programozók tudják,
     * hogy a tömbök 0-tól indexelődnek!!!), valamint az argumentum szövegét.
     */
    printf("%d. argumentum: %s\n", (i + 1), argv[i]);
    /*                             ~~~~~~~
     *                             ^ a printf-ben az értékek helyére tetszőleges
     *                             (megfelelő típusú) KIFEJEZÉS írható, nem csak
     *                             egy egyszerű változó értékének kiírása.
     */
    /* A tömbök indexelése a [] operátorral végezhető el, melybe a kiolvasandó
     * elem indexét írjuk. Ez az index NEM LEHET TÖBB, mint a tömb hossza - 1
     * (mivel a helyes indexek 0-tól kezdődnek), különben a program viselkedése
     * nem definiált (undefined behaviour), amely korrupt memória olvasásához,
     * a program halálához vezet.
     */
    /*                      ~~              ~~~~~~~
     *                      ^ az argumentumok szövegek
     *                                      ^ argv char** típusú, azaz char*,
     *                                      vagy char* -ok tömbje, így amikor
     *                                      egy elemét kivesszük, az char*
     *                                      típusú lesz, amelyet -- JELEN
     *                                      ESETBEN, mivel a char* hivatalosan
     *                                      1 darab (!) char-ra mutat, csak
     *                                      ha helyes string, akkor használható
     *                                      stringként is -- karakterláncként
     *                                      kiírunk.
     */
  }

  return 0;
}
