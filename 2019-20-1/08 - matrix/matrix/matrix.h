#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h> /* size_t */
#include <stdio.h> /* FILE* */

/* typedef: típusszinoníma bevezetése. A felhasználói kódban a 'Matrix' szó
 * helyére az 'int * *' típust értjük. A 'Matrix' nem egy új típus olyan
 * értelemben, hogy oda-vissza konvertálható 'int * *'-ra külön kérés
 * nélkül. Bárhol, ahol egyébként 'int * *' változó szerepel, annak értékül
 * adható egy 'Matrix' "típusú" is.
 */
typedef int             Matrix_Element;
typedef Matrix_Element* Matrix_Row;     /* int *  */
typedef Matrix_Row*     Matrix;         /* int ** */

/* ---------------------------- Memóriaműveletek --------------------------- */

/* Lefoglal egy (rows × cols) méretű mátrixot. Ha a foglalás bármely lépése nem
 * sikerül, a mátrix nem jön létre, és a visszatérési érték NULL.
 */
Matrix matrix_create(size_t rows, size_t cols);

/* Felszabadítja a megadott számú (rows) sorral rendelkező mátrixot. */
void matrix_destroy(Matrix M, size_t rows);

/* ---------------------------------- I/O ---------------------------------- */

/* Beolvassa a megadott F fájlból ("sima" scanf esetén 'stdin') a megadott
 * megfelelő méretű mátrixba SORFOLYTONOSAN az elemeket.
 */
void matrix_fscanf(FILE* F, Matrix M, size_t rows, size_t cols);

/* Kiírja a mátrix tartalmát szépen formázva a megadott kimeneti fájlba
 * ("sima" printf esetén 'stdout').
 */
void matrix_fprintf(FILE* F, Matrix M, size_t rows, size_t cols);

#endif // MATRIX_H
