#ifndef POSITIONAL_NUMS_H
#define POSITIONAL_NUMS_H

/* Kiírja a paraméterben megadott num szám pow_of_10 helyiértékén lévő számot
 * és a helyiérték suffix-ét a standard outputra, majd visszatér a
 * helyiérték szerinti maradékkal.
 *
 * Pl. print_positional(2008, 3, "ezer")
 *    10 a 3-on: 1000
 *    kiírja "két ezer"
 *    visszatér 8.
 */
int print_positional(int num, int pow_of_10, const char * suffix);

#endif // POSITIONAL_NUMS_H
