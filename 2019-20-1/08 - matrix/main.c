#include "matrix/matrix.h"
#include "matrix/algorithm/determinant.h"

#include <stddef.h> /* size_t */
#include <stdio.h> /* printf, scanf */

int main(void)
{
    size_t N, M;
    scanf("%zu %zu", &N, &M);

    if (N != M)
    {
        fprintf(stderr, "Nem négyzetes mátrixnak nincs determinánsa!\n");
        return 1;
    }

    printf("Mx ∈ R^(%zu × %zu)\n", N, M);

    Matrix Mx = matrix_create(N, M);   /* minden mallochoz ... */

    matrix_fscanf(stdin, Mx, N, M);

    matrix_fprintf(stdout, Mx, N, M);
    printf("\n\n");

    bool DetErr = false; /* Létrehozunk egy hibaváltozót, amiben a számoló
                          * függvény jelezni tudja a hiba tényét.
                          */
    int Det = determinant(Mx, N, &DetErr);

    if (DetErr)
        fprintf(stderr, "A determináns számolása közben hiba történt!\n");
    else
        printf("det(Mx) = %d\n", Det);

    matrix_destroy(Mx, N);             /* ... tartozik egy free */
}
