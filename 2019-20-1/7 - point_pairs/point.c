#include "point.h"
#include <stdio.h>

struct Point read_a_point(void)
{
    struct Point p;

    printf("\tx = ");
    scanf("%d", &p.x);
    printf("\ty = ");
    scanf("%d", &p.y);

    return p;
}
