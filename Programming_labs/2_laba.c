#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Вариант 1
int main() {
    double z1, z2;
    double a;

    scanf("%lf", &a);

    z1 = sin(M_PI/2 + 3 * a)/(1 - sin(3 * a - M_PI));
    printf("%lf\n", z1);


    z2 = atan(5 * M_PI / 4 + 3 * a / 2);
    printf("%lf\n", z2);

    return 0;
}