#include <stdbool.h>
#include "vec.h"
#include "object.h"
#include "camera.h"
#include "light.h"

#ifndef RAY_H
#define RAY_H

bool ray_triangle_intersection(Vec3, Vec3, Vec3, Vec3, Vec3, float*, float*, float*);

bool intersect(Mesh, Vec3, Vec3, float*);

Vec3UC castRay(int, Vec3, Vec3, Light, OBJ *, int);

ArrayUC render(Camera, int, Light, OBJ[], int);

#endif