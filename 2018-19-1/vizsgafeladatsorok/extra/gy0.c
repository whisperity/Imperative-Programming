/*
Írjon C függvényt, amely a paraméterként kapott stringet nagybetűssé konvertálja. Kérjen be a felhasználótól egy szót, és alkalmazza rá a megírt függvényt, majd jelenítse meg az eredményt.
*/


#include <stdio.h>
#include <string.h>

char upcase_char(char ch)
{
    return ch - ('a' - 'A');
}

void upcase(char source[], int size)
{
    for (int idx = 0; idx < size; ++idx)
    {
        if (source[idx] >= 'a' && source[idx] <= 'z')
            source[idx] = upcase_char(source[idx]);
    }
}

int main()
{
    char string[256];
    printf("Enter a word: ");
    scanf("%s", string);
    upcase(string, strlen(string));
    printf("Result: '%s'\n", string);
    return 0;
}
