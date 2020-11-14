#define _USE_MATH_DEFINES // Подключаем математические константы
#include <math.h>

// Расчёт длины внутренней окружности
float Lb(int Rb) {
    int x = 2 * M_PI * Rb;
    return x;
}

// Расчёт длины внешней окружности
float Lh(int Rh) {
    int x = 2 * M_PI * Rh;
    return x;
}

float S(int Rb, int Rh) {
    int x = M_PI * (Rh*Rh - Rb*Rb);
    return x;
}