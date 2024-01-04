#include "vec.h"
#include "object.h"
#include "camera.h"

#ifndef RAY_H
#define RAY_H

unsigned ray_triangle_intersection(Vec3D, Vec3D, Vec3D, Vec3D, Vec3D, double*, double*, double*);

ArrayUC object_intersection_test(Camera, Mesh);

#endif