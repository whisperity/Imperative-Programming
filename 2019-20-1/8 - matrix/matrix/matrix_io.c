#include "matrix.h"

#include <stdio.h> /* fprintf, fscanf */

void matrix_fscanf(FILE* F, Matrix M, size_t rows, size_t cols)
{
    /* Beolvasásnál a mátrix elemei sorfolytonosan következnek a bemenetben
     * ami ennek a függvénynek szempontjából lehet akár egy diszken lévő
     * fájl, akár standard input...
     *
     * Így elég csak (rows * cols) darab számot elfogyasztani az inputról.
     */
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            /* scanf(format, ...) === fscanf(stdin, format, ...) */
            fscanf(F, "%d", &M[i][j]);
}

void matrix_fprintf(FILE* F, Matrix M, size_t rows, size_t cols)
{
    /* Kiírásnál a mátrixot (többnyire, mert nem foglalkozunk azzal, hogy
     * jobbra legyen igazítva az összes oszlop ha esetleg van negatív szám...)
     * szépen kiírjuk, soronként a sorokat, szóközzel elválasztva a számokat.
     */

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < rows; ++j)
            printf("%d ", M[i][j]);
        printf("\n"); /* sorvégi 'ENTER' amikor az i-edik sor összes
                              * eleme kiíródott... */
    }
}
