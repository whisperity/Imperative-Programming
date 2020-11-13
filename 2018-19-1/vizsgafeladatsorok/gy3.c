/*
Írjon tartalmazásvizsgálat függvényt sztringekre: Egy adott sztringben keressük az első olyan indexet, ahol egy adott mintasztring bármelyik karaktere előfordul. Amennyiben a minta egyetlen karaktere sem fordul elő az adott sztringben, a függvény visszatérési értéke legyen -1. Mutassa be a függvény működését.

Példa input:
"This is my first string", minta: "first"

Elvárt output:
2
*/


#include <stdio.h>

int strany(const char str[], const char sample[])
{
    int i = 0, j = 0;
    while (str[i] != '\0')
    {
        while (sample[j] != '\0')
        {
            if(str[i] == sample[j])
                return i;
            ++j;
        }
        ++i;
        j = 0;
    }
    return -1;
}

int main()
{
    printf("result: %d\n", strany("This is my first string", "first"));
    return 0;
}
