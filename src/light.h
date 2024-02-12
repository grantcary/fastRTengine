#include "vec.h"

#ifndef LIGHT_H
#define LIGHT_H

typedef struct {
    unsigned type; // 0: sun
    Vec3 position;
    Vec3 direction;
    float intensity;
} Light;

#endif