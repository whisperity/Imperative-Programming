#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC_VAR(Type, Var, Count) \
    Type *Var = malloc(sizeof(Type) * (Count))

size_t strchrcnt(const char *Str, const char Chr);
void extract_commasep_numbers(const char *InStr,
                              int **Arr);
void print_ints(int **Arr, size_t N);
void bouncing_delete(int **Arr, size_t N);

void delete_multiples_of_between(int ** Left,
                                 int ** const Right,
                                 int ** const Element);

bool is_multiple(int x, int y);
int** max(int **Arr, size_t N);
int** min(int **Arr, size_t N);

/* Memória modell: számok vannak malloc-olva valahol. Ezekre mutató
 * pointerek vannak eltárolva egy tömbben. A tömb elemet NULL-ra
 * állítva, és a számot free()-elve tudjuk jelezni, hogy egy számot
 * "töröltünk" a tömbből.
 */

/* A Repl.it sajátosságai miatt most nem argv[1]-ből dologzunk,
hanem a standard inputról, mert Repl.it-en nehéz commandline
argumentumokat megadni... :( */
int main(void)
{
    printf("Give me a comma separated list of numbers, like "
           "\"1,2,3,4\"! \n\t");
    char In[4096];
    if (!fgets(In, sizeof(In), stdin))
    {
        fprintf(stderr, "Szöveges bemenet olvasási hiba!\n");
        return 1;
    }

    size_t NumNums = strchrcnt(In, ',') + 1;
    MALLOC_VAR(int *, Input, NumNums);
    extract_commasep_numbers(In, Input);
    if (!Input)
    {
        fprintf(stderr, "Memória foglalás hiba!\n");
        return 2;
    }

    fprintf(stderr, "Kezdünk: ");
    print_ints(Input, NumNums);
    fprintf(stderr, "\n");

    bouncing_delete(Input, NumNums);
    fprintf(stderr, "Vége.\n");
    
    free(Input);
}

void print_ints(int **Arr, size_t N)
{
    bool AnyPrinted = false;

    for (size_t I = 0; I < N; ++I)
    {
        if (!Arr[I])
            continue;
        fprintf(stderr, "%d ", *Arr[I]);
        AnyPrinted = true;
    }

    if (!AnyPrinted)
        fprintf(stderr, "<üres>");
}

void bouncing_delete(int **Arr, size_t N)
{
    int **End = Arr + (N - 1); /* A tömb jobb széle. */
    while (true)
    {
        int **Min = min(Arr, N);
        if (!Min)
            return;

        printf("Minimum: %d\n", **Min);

        fprintf(stderr, "Törlés jobbra: ");
        print_ints(Arr, N);
        fprintf(stderr, " -> ");

        /* Törlés "jobbra": a minimumtól a végéig. */
        delete_multiples_of_between(Min, End, Min);

        print_ints(Arr, N);
        fprintf(stderr, "\n");
        
        /* ------------------------------------------ */
        int **Max = max(Arr, N);
        if (!Max)
            return;

        printf("Maximum: %d\n", **Max);

        fprintf(stderr, "Törlés balra: ");
        print_ints(Arr, N);
        fprintf(stderr, " -> ");

        /* Törlés "balra": az elejétől a maximumig. */
        delete_multiples_of_between(Arr, Max, Max);

        print_ints(Arr, N);
        fprintf(stderr, "\n");
    }
}

void delete_multiples_of_between(int ** Left,
                                 int ** const Right,
                                 int ** const Element)
{
    /* Kitörli "left" és "right" között (amely az int *-okat
     * tartalmazó tömb egy-egy elemére mutat!) az 'Element'
     * által mutatott tömbelem által mutatott szám többszöröseit.
     */
    if (!(Left <= Element) || !(Element <= Right))
    {
        fprintf(stderr,
            "Algoritmus hiba: a törlési tömb rész rosszul "
            "lett kiválasztva! Left <= E <= Right, azaz "
            "E € [Left, Right] fenn kéne álljon...!\n");
        exit(-1); /* program kényszeres vége! */
    }

    int E = **Element;
    for (; Left <= Right; ++Left)
    {
        /* A "Left" kezdetben az első elem, ahonnan indulva
         * törlök, ezzel megyek jobbra a tömbben.
         */
        if (!*Left)
            /* Törlés közben kihagyjuk a már törölt elemeket! */
            /* A törölt elem a TÖMBBEN NULL, a LEFT a tömb *ELEMÉRE*
             * mutat, ami mindig nem null. A tömb elemét kell
             * vizsgálni!
             */
            continue;

        if (is_multiple(**Left, E))
        {
            /* Left -> int**, a pointerek tömbjébe mutat. */
            free(*Left); /* *Left -> int*, a konkrét számra mutat. */
            *Left = NULL; /* A tömb elemet (!) NULL-ra állítjuk. */
        }
    }
}

size_t strchrcnt(const char *Str, const char Chr)
{
    size_t N = 0;
    while (*Str != '\0')
    {
        if (*Str == ',')
            ++N;
        ++Str;
    }
    
    return N;
}

void extract_commasep_numbers(const char *InStr,
                              int **Arr)
{
    while (InStr != NULL)
    {
        /* Feldolgozzuk a stringet. */
        /* Arr int*-ok tömbjének egy elemére (kezdetben első,
         * majd léptetődik...) mutat.
         */
        /* lefoglalunk a beolvasandó számnak egy helyet, és
         * eltesszük a tömbbe *A HELYÉRE MUTATÓ POINTERT!*
         */
        *Arr = malloc(sizeof(int));
        
        if (sscanf(InStr, "%d", *Arr) != 1)
        {
        /*                      ^~~~
         *      típusa int*, a malloc() visszatérési
         *      értéke, erre a CÍMRE olvasunk be!
         */
            fprintf(stderr, "Olvasási hiba!\n");
            exit(3);
        }
        ++Arr; /* Arr tömb következő elemére lépünk. */

        /* Elmegyünk a következő , -ig... */
        InStr = strchr(InStr, ',');
        if (!InStr)
            /* strchr() NULL-t ad vissza, ha már nincs vessző */
            break;

        ++InStr; /* Az InStr ne a vesszőre, hanem a rákövetkező
                    betűre mutasson. */
        /* Minden stringben tovább tolt pointer egy szuffix, de
         * valódi string, amíg nem értük el az első bináris nullát.
         *
         * Azaz: char *S = "ELTE";
         * esetén:
         *     ++S után S az "LTE"-re,
         *     még egy ++S után a "TE"-re
         * mutat.
         */
        
    }
}

bool is_multiple(int x, int y)
{
    /* x többszöröse y, ha létezik olyan egész z, hogy x = y * z */
    /* a z most érdektelen. Az a lényeg, hogy "x = y * z + r"-ben
     * r, a maradék, 0.
     */
    return x % y == 0;
}

int** min(int **Arr, size_t N)
{
    int **MinCandidate = NULL;
    size_t I = 0;
    for (; I < N; ++I)
    {
        /* Megkeressük az első nem NULL elemet. A legelső
         * elem lehet, hogy NULL, így az általa mutatott nem jó
         * "kezdeti minimum" választás.
         */
        if (Arr[I])
        {
            MinCandidate = &Arr[I];
            break;
        }
    }
    if (!MinCandidate)
        /* Elfogyott a tömb, senki se minimum. */
        return NULL;

    for (; I < N; ++I)
    {
        /* I a korábbi ciklus abbahagyásakori index. Megyünk tovább,
         * keresve egy jobb minimumot.
         */
        if (Arr[I] && *Arr[I] < **MinCandidate)
            MinCandidate = &Arr[I];
    }
    return MinCandidate;
}

int** max(int **Arr, size_t N)
{
    int **MaxCandidate = NULL;
    size_t I = 0;
    for (; I < N; ++I)
    {
        if (Arr[I])
        {
            MaxCandidate = &Arr[I];
            break;
        }
    }
    if (!MaxCandidate)
        /* Elfogyott a tömb, senki se maximum. */
        return NULL;

    for (; I < N; ++I)
    {
        if (Arr[I] && *Arr[I] > **MaxCandidate)
            MaxCandidate = &Arr[I];
    }
    return MaxCandidate;
}
