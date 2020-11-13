#ifndef MATRIX_ALGORITHM_DETERMINANT_H
#define MATRIX_ALGORITHM_DETERMINANT_H

#include "../matrix.h"

#include <stdbool.h> /* bool */

/* Kiszámolja a megadott Mx (Dim × Dim méretű, négyzetes) mátrix
 * determinánsát, rekurzívan, kifejtési tétellel.
 *
 * Amennyiben a rekurzió során hiba következik be, az Err-ben átadott
 * pointer által mutatott "hibaváltozót" igazra állítja, jelezvén a hívónak a
 * hiba tényét.
 */
int determinant(Matrix Mx, size_t Dim, bool* Err);

#endif // MATRIX_ALGORITHM_DETERMINANT_H
