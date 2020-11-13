/* A főprogram fordítási egységéhez szükségünk van a Point és PointPair
 * típusokra.
 */
#include "point.h"
#include "point_pair.h"  /* PointPair függ Point-tól, így ez a header behúzná
                          * point.h -t mégegyszer, ami, ha nem lenne header
                          * guard, azonnal fordítási hibához vezetne.
                          */
#include <stdio.h> /* prinf, scanf */
#include <stdlib.h> /* malloc, free */

/* A klasszikus, idiomatikus malloc mantra N darab T típusokból álló terület
 * foglalására és arra P pointer állítása. Makróban. */
#define MANTRA(T, P, N) \
    T* P = (T*)(malloc(sizeof(T) * (N)))

int main(void)
{
    printf("Hány pontot fogsz adni? ");
    size_t N;
    scanf("%zu", &N);

    if (N < 2)
    {
        perror("Párokat kell generálnom, ahhoz pedig legalább 2 elem kell!");
        return 1;
    }

    /* MANTRA(struct Point, Points, N); */
    struct Point* Points = (struct Point*)malloc(sizeof(struct Point) * N);
    /* Ugyanúgy malloc-olunk, mintha int-ek lennének, csak most pontokat
     * foglalok le.
     */
    if (!Points) { perror("Nem sikerült a memória foglalás."); return 1; }

    for (size_t i = 0; i < N; ++i)
    {
        printf("Kérem a(z) %zu. pontot!\n", i + 1);
        Points[i] = read_a_point(); /* Points egy 'struct Point *'. Ennek
                                     * indexelésével egy konkrét
                                     * 'struct Point'-t kapunk (az i-ediket),
                                     * amelynek értékül adni valamit megintcsak
                                     * értelmes, és tagonkénti másolást jelent.
                                     */
    }

    printf("x1 = %d, y1 = %d\n", Points[0].x, Points[0].y);
    printf("x2 = %d, y2 = %d\n", Points[1].x, Points[1].y);
    /*                           ^~~~~~~~~
     *                           a Points mögötti memóriaterület 1 indexű eleme,
     *                           egy konkrét elem, amely 'struct Point' típusú
     */

    struct PointPair PP = make_pair(Points[0], Points[1]);
    printf("Az első két pont távolsága:\n");
    printf("\t(%d, %d) --> (%d, %d): %f\n",
           PP.a.x, PP.a.y,
        /* ^~~~~~  ^~~~~~  A pontpár "első" mezőjének két mezője. */
           PP.b.x, PP.b.y, /* ... hasonlóan a másodikra. */
           PP.distance);   /* ... és a kiszámított távolság. */

    struct PointPair PPi = make_pair(Points[1], Points[0]);
    printf("Az első két pont távolsága, csak fordított irányban:\n");
    printf("\t(%d, %d) --> (%d, %d): %f\n",
           PPi.a.x, PPi.a.y,
           PPi.b.x, PPi.b.y,
           PP.distance);

    free(Points);

    return 0;
}
