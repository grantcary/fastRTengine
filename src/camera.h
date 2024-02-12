#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

typedef struct {
    Vec3 position;
    Array origins, directions;
    int max_depth;
} Camera;

Camera initializationCamera(int, int, float, Vec3);

#endif