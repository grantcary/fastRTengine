#include <stdbool.h>
#include "vec.h"
#include "object.h"
#include "camera.h"
#include "light.h"

#ifndef RAY_H
#define RAY_H

bool ray_triangle_intersection(Vec3D, Vec3D, Vec3D, Vec3D, Vec3D, double*, double*, double*);

bool intersect(Mesh, Vec3D, Vec3D, double *);

Vec3UC castRay(int, Vec3D, Vec3D, Light, OBJ *, int);

ArrayUC object_intersection_test(Camera, int, Light, OBJ[], int);

#endif