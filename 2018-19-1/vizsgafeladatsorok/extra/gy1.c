/*
Írjon C/Python függvényt, amely a paraméterként kapott sztringet pozitív egész számmá konvertálja. További nehezítés, hogy a sztring elején tetszőleges számú szóköz lehet, ezeket a függvény hagyja figyelmen kívül. Feltehető, hogy a sztringben csak a szóköz és 0-9 karakterek szerepelnek. Mutassa be a függvény működését.

(Python választás esetén az int(string) nem elfogadható megoldás)

Példa input:
"     5684"

Elvárt output:
5684
*/


#include <stdio.h>

static const int NUMERAl_BASENUM = 10;

int strtoint(const char string[], int size)
{
    int result = 0;
    int idx = 0;

    while (idx < size && string[idx] == ' ')
        ++idx;

    for (; idx < size; ++idx)
    {
        result = NUMERAl_BASENUM * result + (string[idx] - '0');
    }
    return result;
}

int main()
{
    printf("result: %d\n", strtoint("     5684", 9));
    return 0;
}
