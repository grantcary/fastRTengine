#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

typedef struct {
    Vec3D position;
    ArrayD origins, directions;
} Camera;

Camera initializationCamera(int, int, float, Vec3D);

#endif