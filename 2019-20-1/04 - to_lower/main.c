/* Mivel a projektünk több fájlból áll, a további fordítási egységekhez
 * tartozó fejlécállományokat is be kell #include -olni. */
/* A saját headereket "" között includeoljuk: a fájlnév alapján a tényleges
 * fájl keresése a helyi mappából indul. */
#include "to_lower.h"

/* Szükséges a main.c fordításához az stdio (printf miatt)
 * és a string (strlen miatt). */
/* A rendszer headereket <> között includeoljuk: a fájlnév alapján a tényleges
 * fájl keresése a rendszerre telepített hierarchiából és a rendszergazdák
 * által beállított elérési útvonalakról (általában /usr/include) kerül
 * betöltésre. */
#include <stdio.h>
#include <string.h>

/* Az fontos, hogy a saját és a rendszer headerek include-olását ne vegyítsük.
 * Bár jól megírt headerek esetén nincs negatív hatása a vegyítésnek,
 * nehezen olvashatóvá teszi a kódot.
 */

int main(int argc, char** argv)
{
    /* Feladat: Írjuk ki az összes parancssori argumentumot, de kisbetűsre
     * alakítva.
     */
    
    for (int i = 1; i < argc; ++i)
    {
        /* Ez a ciklus mint az 'echo' példában:
         * https://repl.it/@whisperity/imp1920163-echo
         */
        /* (Az első elem kimarad (1-től indulunk, nem 0-tól), mert a program
         * neve nem érdekel minket.
         */
        
        /* Mielőtt az argv[i] -t kiírnánk, meghívjuk a to_lower() függvényt,
         * amely kisbetűsre alakítja a karaktersorozatban található nagybetűket.
         */
        to_lower(strlen(argv[i]) + 1, argv[i]);
        printf("%s ", argv[i]);
    }

    printf("\n");
    return 0;
}
