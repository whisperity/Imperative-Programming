#include <stdio.h>
#include <stdlib.h>

#define MALLOC_VAR(Type, Var, Count) \
    Type *Var = malloc(sizeof(Type) * (Count))

int read_int(const char *Prompt);
void read_ints(int * const Arr, const size_t N);
void print_nums(int * const Arr, const size_t N);

void sieve_parity(
    const int * const Input,
    const size_t InSize,
    int * OutOdds,
    int * OutEvens,
    size_t * const OddsN,
    size_t * const EvensN);

int main(void) {
    int N = read_int("Hány elemű a tömb?");
    int K = read_int("Az első hány elemet rendezzem?");
    if (N < 0 || K < 0)
    {
        fprintf(stderr, "Érvénytelen input: negatív elemszám.\n");
        return 1;
    }
    if (N < K)
    {
        /* Egy 8 elemű tömb első 10 eleme a 8 elem. :) */
        K = N;
    }

    MALLOC_VAR(int, Input, N);
    MALLOC_VAR(int, Odds, K);
    MALLOC_VAR(int, Evens, K);

    if (!Input || !Odds || !Evens)
    {
        fprintf(stderr, "Nem sikerült a memória foglalás.\n");

        /* Ha valamelyik foglalás nem sikerült, null pointer.
        Azt free()-elni jól definiált: nem történik semmi. */
        free(Evens);
        free(Odds);
        free(Input);

        return 2;
    }

    read_ints(Input, N);

    size_t No, Ne;
    sieve_parity(Input, K, Odds, Evens, &No, &Ne);

    printf("Párosok:\n\t");
    print_nums(Evens, Ne);
    
    printf("Páratlanok:\n\t");
    print_nums(Odds, No);

    free(Evens);
    free(Odds);
    free(Input);
    return 0;
}

int read_int(const char *Prompt)
{
    printf("%s ", Prompt);
    int i;
    scanf("%d", &i);
    return i;
}

void read_ints(int * const Arr, const size_t N)
{
    printf("Reading %zu integers...\n", N);
    char Prompt[32];

    for (size_t I = 0; I < N; ++I)
    {
        /* kiírjuk, hogy hanyadik elemet olvassuk */
        sprintf(Prompt, "[%zu/%zu]: ", I + 1, N);
        Arr[I] = read_int(Prompt);
    }
}

void print_nums(int * const Arr, const size_t N)
{
    for (size_t I = 0; I < N; ++I)
    {
        printf("%d ", Arr[I]);
    }
    printf("\n");
}

void sieve_parity(
    const int * const Input,
    const size_t InSize,
    int * OutOdds,
    int * OutEvens,
    size_t * const OddsN,
    size_t * const EvensN)
{
    *OddsN = *EvensN = 0;

    for (size_t I = 0; I < InSize; ++I)
    {
        if (Input[I] % 2 != 0)
        {
            ++*OddsN;

            *OutOdds = Input[I];
            ++OutOdds;
        }
        else
        {
            ++*EvensN;

            *OutEvens = Input[I];
            ++OutEvens;
        }
    }
}
