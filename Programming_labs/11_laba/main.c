#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "ring.h"
#include "geometry.h"

int main() {

    int Ax;
    int Ay;
    int Rb;
    int Rh;

    printf("%s", "Input points: \n");
    printf("Ax = ");
    scanf("%d", &Ax);
    printf("Ay = ");
    scanf("%d", &Ay);

    printf("%s", "Input B Radius and H Radius: \n");
    printf("Rb = ");
    scanf("%d", &Rb);
    printf("Rh = ");
    scanf("%d", &Rh);

    struct Ring P = FormStruct(Ax, Ay, Rb, Rh);

    int LB = Length_b(P.Rb.Rb);
    printf("Length_b: %d\n", LB);

    int LH = Length_h(P.Rb.Rh);
    printf("Length_h: %d\n", LH);

    int square = S(P.Rb.Rb, P.Rb.Rh);
    printf("Square: %d", square);
    return 0;
}
