#include "vec.h"

#ifndef LIGHT_H
#define LIGHT_H

typedef struct {
    unsigned type; // 0: sun
    Vec3D position;
    Vec3D direction;
    float intensity;
} Light;

#endif