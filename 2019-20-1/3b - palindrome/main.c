#include <stdio.h>
#include <string.h>  /* strlen() a string.h-ból használandó */

int main(int argc, char** argv)
{
  /* ------------------------------- FELADAT ------------------------------- */
  /* Írj egy programot, amely pontosan 1 darab paramétert vár parancssori
   * argumentumként, és megmondja, hogy a kapott "szó" palindróma-e.
   *
   * Palindrómák azok a szavak, amelyek előlről és hátulról olvasva ugyanazok.
   *
   * Például palindróma: görög, xazax, apa, racecar
   * Nem palindróma: török, kutya, whisperity
   */
  /* Repl.it -en nem biztos, hogy működni fog a program, mert nem tudunk
   * parancssori argumentumokat megadni.
   */

  /* A palindrómaság ellenőrzéséhez be kell járnunk az inputként kapott szót,
   * és ellenőrizni az összes betűpárt - ha az első és utolsó betű ugyanaz,
   * ha a második és az utolsó előtti, stb..., ez az ÖSSZES PÁRRA teljesül,
   * akkor palindróma.
   * Ha találunk egy olyan betűpárt, amely nem egyezi, akkor nem.
   *
   * Páratlan hosszú szavaknál a középső betű nem áll párban semelyikkel, így
   * azt nem kell ellenőrni.
   */
  char* word = argv[1];      /* Elnevezzük a 2. paramétert (az 1. a program
                                neve) valamilyen egyszerűen használható néven.*/
  int length = strlen(word); /* Lekérdezzük a szó hosszát. strlen-nek helyes
                                stringeket kell átadni, hogy működjön.
                                A hossz a "valódi" betűk száma, a null
                                terminátort nem veszi figyelembe! */

  for (int i = 0; i < length / 2; ++i)
  /*                  ~~~~~~~~~~
   *                  ^ mivel a betűpárokat kell ellenőrzni, elég a ciklust
   *                  a szó első felére (a középső elemet nem figyelembe véve,
   *                  ha páratlan lenne, így most jó, hogy length / 2 lefelé
   *                  kerekít!) futtatni.
   */
  {
    /* Felveszünk két segédváltozót, amely megmondja, hogy az aktuális lépésben
     * a betűpár a szó elejéről hanyadik, és hátuljáról hanyadik betűből áll.
     */
    int front_index = i;
    /* A 0. indexű betű párja az utolsó lehetséges index. Például 5 hosszú
     * szónál a 4 (mivel az 5 indexű "betű" (a "hatodik") a null-terminátor!)
     * Ezért amikor a szó végéről indulunk, akkor az utolsó index (length - 1),
     * ebből kell vissza haladni 'i' darab betűt.
     */
    int back_index = length - 1 - i;

    printf("Összehasonlítom a (%d, %d) indexeken lévő betűket: ",
           front_index, back_index);
    printf("%c , %c\n", word[front_index], word[back_index]);
    /*      ~~   ~~     ~~~~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~~~
     *                  ^ word (argv[1]) típusa char*, így a tömböt megindexelve
     *                  egy konkrét karaktert kapunk!
     */

    /* Amennyiben a feladat úgy szól, hogy "ha mindenre teljesül igaz", a
     * megoldás logikája a ciklusban a nem teljesülést keresni.
     * Ha találunk (legalább) egy nem egyezőt, akkor rámondhatjuk, hogy nem
     * igaz... [[1]]
     */

    if (word[front_index] != word[back_index])
    {
      printf("    Ez a pár nem egyezett... nem palindróma!\n");
      return 1; /* A main()-beli return azonnal "kivégzi" a ciklust és
                   leállítja a programot, ami most jó, hiszen rájöttünk, hogy
                   nem palindróma, felesleges tovább vizsgálódni. */
    }
  }

  /* [[1]]... de azt, hogy igaz, csak akkor mondhatjuk rá, ha MINDEN elemre
   * teljesült.
   *
   * Gondoljunk a MatAlapra: "minden x-re P" ellentettje: "létezik x amelyre !P"
   */
  printf("Minden párra teljesül: palindróma szó!\n");
  return 0;
}
