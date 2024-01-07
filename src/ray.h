#include <stdbool.h>
#include "vec.h"
#include "object.h"
#include "camera.h"

#ifndef RAY_H
#define RAY_H

bool ray_triangle_intersection(Vec3D, Vec3D, Vec3D, Vec3D, Vec3D, double*, double*, double*);

bool intersect(Mesh, Vec3D, Vec3D, double *);

Vec3UC test_objects(Vec3D, Vec3D, OBJ[], int);

ArrayUC object_intersection_test(Camera, OBJ[], int);

#endif