#include "matrix.h"

#include <stdlib.h> /* malloc, free */

Matrix matrix_create(size_t rows, size_t cols)
{
    /* Statikus (fordítási időben ismert) méretű mátrixok, pl.
     *     int M[4][4];
     * esetén működik a "tömbös" indexelés: M[0][1] = 4;
     * Azonban ha 'int *'-ként próbálunk egy sorfolytonos N*M méretű tömböt
     * foglalni, azt nem lehet "tömbösen" indexelni (legalábbis kétszer),
     * hiszen az első indexelés eredménye már 'int' ami nem indexelhető
     * tovább.
     *
     * Mátrixok tárolására két lehetőségünk van, ha dinamikus mérettel
     * dolgozunk:
     *   1. Sorfolytonos tömb készítése (fenti példában 16 mérettel), és
     *      az {i, j} indexeket "kézzel" egy függvényben mindig átszámoljuk
     *      [0, i*j) indexekre.
     *   2. "Tömbök tömbjét" foglalunk, ahol a "külső" tömb (ami a "mátrix
     *      változónk") igazából csak pointereket tárol a sorokra, amelyek
     *      az elemeket tartalmazzák.
     *
     * Az első megoldás részletei valószínűleg "Algoritmusok és
     * adatszerkezetek" tárgyból lesznek majd.
     *
     * A jelenlegi kód a második megoldást valósítja meg.
     * A második megoldás egyszerűbb kódot biztosít, mivel működik az
     *     M[0][1]
     * jellegű indexelés, viszont *DRÁGÁBB*, mivel plusz pointer-dereferálás
     * történik a használata során.
     * (Nagyon nagy méretű mátrixoknál ennek már mérhető költsége van...)
     *
     * +---+        +---+        +----+----+-----+----+
     * | M | -->    | * | -->    | 1  | 2  | 3   | 4  |
     * +---+        +---+        +----+----+-----+----+
     *              | * | -->    | 10 | 20 | 30  | 40 |
     *              +---+        +----+----+-----+----+
     *              | * | -->    | 67 | 24 | -58 | 12 |
     *              +---+        +----+----+-----+----+
     *              | * | -->    | 2  | 0  | 8   | 0  |
     *              +---+        +----+----+-----+----+
     */

    /* A külső tömb a sorokat (mint számok tömbjének első elemére mutató
     * pointer) fogja tartalmazni, ezért a sizeof-ba 'int *'-ot írunk!
     */
    Matrix M = malloc(rows * sizeof(Matrix_Row)); /* sizeof(int *) */
    if (!M)
        return NULL;

    /* Eddig a pontig van 'rows' darab memóriaszemét értékkel rendelkező
     * pointerünk...
     */

    for (size_t i = 0; i < rows; ++i)
    {
        M[i] = malloc(cols * sizeof(Matrix_Element)); /* sizeof(int) */
    /*  ^~~~
     *  M típusa 'int**', azt egyszer megindexelve 'int*'-ot kapunk, aminek egy
     *  másik 'int*' értékül adható.
     */

        /* Mi történik, ha az i-edik sor allokálása nem sikerül?! Ebben az
         * esetben a teljes mátrix nem tud létrejönni, de az i előtti sorokat
         * már allokáltuk... ezt fel kell szabadítani, hogy ne okozzunk
         * memory leak-et.
         */
        if (!M[i])
        {
            for (size_t k = 0; k < i; ++k)
                free(M[k]);
            free(M);

            return NULL;
        }
    }

    return M;
}

void matrix_destroy(Matrix M, size_t rows)
{
    /* Felszabadításnál belülről kifelé haladva szabadítunk fel. A mátrixot
     * reprezentáló "tömbben" pointerek vannak a sorok elemeit tartalmazó
     * tömbök első elemére. Mielőtt a mátrix "-1." oszlopát felszabadítanánk,
     * a sorokkal kell elbánnunk, ha M megszűnik létezni, soha többet nem
     * szerezzük vissza, hogy a sorok hol voltak a memóriában.
     */
    for (size_t i = 0; i < rows; ++i)
        free(M[i]);
    free(M);
}
