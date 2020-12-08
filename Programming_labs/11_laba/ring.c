#define _USE_MATH_DEFINES // Подключаем математические константы
#include <math.h>
#include "ring.h"
#include "geometry.h"

struct Ring FormStruct(int Ax, int Ay, int Rb, int Rh) {
    struct point a;
    a.x = Ax;
    a.y = Ay;

    struct point b;
    b.Rb = Rb;

    struct point c;
    b.Rh = Rh;

    struct Ring P;
    P.A = a;
    P.Rb = b;
    P.Rh = c;

    return P;
};

// Расчёт длины внутренней окружности
int Length_b(int Rb) {
    int x = 2 * M_PI * Rb;
    return x;
}

// Расчёт длины внешней окружности
int Length_h(int Rh) {
    int x = 2 * M_PI * Rh;
    return x;
}

// Расчёт площади
int S(int Rb, int Rh) {
    int x = M_PI * (Rh*Rh - Rb*Rb);
    return x;
}