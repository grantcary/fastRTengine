#include "vec.h"

#ifndef VMATH_H
#define VMATH_H

Vec3D vadd(Vec3D, Vec3D);

Vec3D vsub(Vec3D, Vec3D);

Vec3D cross_product(Vec3D, Vec3D);

double dot_product(Vec3D, Vec3D);

Vec3D normalize(Vec3D);

#endif