#ifndef RING_H_ICLUDED
#define RING_H_ICLUDED

#define _USE_MATH_DEFINES
#include <math.h>

struct ring {
    float Lh;
    float Lb;
    float Rh;
    float Rb;
    float S;
};

float Lh(int);

float Lb(int);

float S(int, int);

#endif
