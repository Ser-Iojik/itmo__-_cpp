#include <stdio.h>
#include <stdlib.h>

// Сначала будут просмотрены локальные (по отношению к проекту) папки включения файлов
#include "point.h"
#include "ring.h"
#include "ring.c"



int main() {

    int Rb;
    int Rh;

    struct point P;

    printf("%s", "Input points: ");

    scanf("%d %d", &P.Rb, &P.Rh);

    printf("%d %d\n", P.Rb, P.Rh);
    printf("Lenght_b: %f\n", Lb(P.Rb));
    printf("Lenght_h: %f\n", Lh(P.Rh));
    printf("S: %f", S(P.Rb, P.Rh));

    return 0;
}
