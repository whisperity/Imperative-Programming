/* Mivel a to_lower.c fájl a to_lower.h -ban lévő dolgokat implementálja, ezért
 * itt is be kell includeolni a megfelelő header-t. Ez azért kell, hogy ha a 
 * függvény egy saját típust használna, akkor az ebben a fordítási egységben is
 * definiált, ismert, értelmes legyen.
 * Valamint, ha esetleg ellentmondásos lenne a headerben írt (és így a hívási
 * helyeken látszó függvény típusa (paraméterezése, stb.)), akkor kapjunk
 * fordítási hibát, hogy rossz függvényt próbálunk meg implementálni.
 */
#include "to_lower.h"

void to_lower(int N, char* S)
{
    /* A függvény implementációjában a tömb minden elemét megvizsgáljuk, hogy
     * valamelyik nagybetű-e, és ha igen, akkor az adott elemet a kisbetűs
     * változatra cseréljük.
     *
     * (Mivel általános "else" ág nincs, ezért a nem nagybetűket (kisbetűk,
     * számok, ékezetes betűk) békén és helyben hagyjuk.)
     */
    for (int i = 0; i < N; ++i)
    {
             if (S[i] == 'A') S[i] = 'a';
        else if (S[i] == 'B') S[i] = 'b';
        else if (S[i] == 'C') S[i] = 'c';
        else if (S[i] == 'D') S[i] = 'd';
        else if (S[i] == 'E') S[i] = 'e';
        else if (S[i] == 'F') S[i] = 'f';
        else if (S[i] == 'G') S[i] = 'g';
        else if (S[i] == 'H') S[i] = 'h';
        else if (S[i] == 'I') S[i] = 'i';
        else if (S[i] == 'J') S[i] = 'j';
        else if (S[i] == 'K') S[i] = 'k';
        else if (S[i] == 'L') S[i] = 'l';
        else if (S[i] == 'M') S[i] = 'm';
        else if (S[i] == 'N') S[i] = 'n';
        else if (S[i] == 'O') S[i] = 'o';
        else if (S[i] == 'P') S[i] = 'p';
        else if (S[i] == 'Q') S[i] = 'q';
        else if (S[i] == 'R') S[i] = 'r';
        else if (S[i] == 'S') S[i] = 's';
        else if (S[i] == 'T') S[i] = 't';
        else if (S[i] == 'U') S[i] = 'u';
        else if (S[i] == 'V') S[i] = 'v';
        else if (S[i] == 'W') S[i] = 'w';
        else if (S[i] == 'X') S[i] = 'x';
        else if (S[i] == 'Y') S[i] = 'y';
        else if (S[i] == 'Z') S[i] = 'z';
    }
}

/* Látható, hogy a függvény nagyon sok sort tartalmaz, amelyben ugyanazon
 * dolgok (nagy mértékben) ismétlődnek: else if, feltétel, értékadás, csak a
 * használt nagy- és kisbetűben tér el, a maradék ugyanaz.
 * 
 * Ebben az esetben célszerű lehet a preprocesszor egy újabb vívmányát, ún.
 * makrókat használni. Makrókat használtunk a header guardok esetén is, ott
 * viszont csak, mint egy logikai értéket, azt vizsgálva, hogy
 * "bebillentették-e" a definiált státuszt.
 * 
 * A makróknak azonban létezhet kifejtése ("értéke"), amelyre a preprocesszor
 * szövegszerűen (!!!) lecseréli a makró előfordulásait, mielőtt a programszöveg
 * érdemi fordítása elindulna. Így egy makró eredménye önmagában nem kell
 * értelmes C kód legyen, csak az a fontos, hogy mire minden makró kifejtődik,
 * értelmes programszöveget kapjunk.
 */

/* ELSE egy paraméter nélküli makró, amely a kisbetűs else kulcsszóra oldódik
 * fel.
 */
#define ELSE else

/* REPLACE egy paraméteres makró két (F és T) paraméterrel. Kifetéskor a
 * makróban szereplő F és T betű lecserélődik a makró használatakor szereplő
 * szövegre(!). A makró maradéka betűről betűre a programszövegbe kerül.
 * Ez az ismétlődő rész fentebbről: a tömb indexelése, elem összehasonlítása,
 * értékadása.
 * A ténylegesen vizsgált karakter (F) és a helyére írt karakter (T) a
 * paraméterből jön.
 */
#define REPLACE(F, T) \
    if (S[i] == F) S[i] = T
        
/* A fordítóprogramtól az -E kapcsolóval elkérhető a teljesen preprocesszált
 * programszöveg, amelyet a fordítóprogram fordítási lépése (amikor már C(/C++)
 * kódot értelmez) feldolgoz.
 * 
 * Pl.:  gcc -E to_lower.c
 * vagy: clang -E to_lower.c
 *
 * Próbáld ki ezt a fájlt, hogy lásd, a to_lower és a to_lower_2 függvények
 * nem különböznek egymástól érdemben.
 */

/* to_lower_2 egy olyan függvény, amelyet meghívni másik fájlból nem lehet
 * "szép" és egyszerű módon, lévén nem ismert a típusozása, és a neve sem.
 * 
 * (Vannak persze lehetőségek, ha a nevet és a típust megadjuk, vagy dinamikusan
 * megkeressük a lefordított binárisban futásidőben, stb.
 */
void to_lower_2(int N, char* S)
{
    for (int i = 0; i < N; ++i)
    {
             REPLACE('A', 'a'); /* Jelentése: if (S[i] == 'A') S[i] = 'a' */
        ELSE REPLACE('B', 'b');
        ELSE REPLACE('C', 'c');
        ELSE REPLACE('D', 'd');
        ELSE REPLACE('E', 'e');
        ELSE REPLACE('F', 'f');
        ELSE REPLACE('G', 'g');
        ELSE REPLACE('H', 'h');
        ELSE REPLACE('I', 'i');
        ELSE REPLACE('J', 'j');
        ELSE REPLACE('K', 'k');
        ELSE REPLACE('L', 'l');
        ELSE REPLACE('M', 'm');
        ELSE REPLACE('N', 'n');
        ELSE REPLACE('O', 'o');
        ELSE REPLACE('P', 'p');
        ELSE REPLACE('Q', 'q');
        ELSE REPLACE('R', 'r');
        ELSE REPLACE('S', 's');
        ELSE REPLACE('T', 't');
        ELSE REPLACE('U', 'u');
        ELSE REPLACE('V', 'v');
        ELSE REPLACE('W', 'w');
        ELSE REPLACE('X', 'x');
        ELSE REPLACE('Y', 'y');
        ELSE REPLACE('Z', 'z');
    }
}
