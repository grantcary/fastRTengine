#include "vec.h"

#ifndef VMATH_H
#define VMATH_H

Vec3D vadd(Vec3D, Vec3D);

Vec3UC uadd(Vec3UC, Vec3UC);

Vec3D vsub(Vec3D, Vec3D);

Vec3D svdiv(Vec3D, double);

Vec3UC umul(Vec3UC, Vec3UC);

Vec3UC sumul(Vec3UC, double);

Vec3D vmul(Vec3D, Vec3D);

Vec3D sdmul(Vec3D, double);

double vsum(Vec3D);

Vec3D cross_product(Vec3D, Vec3D);

double dot_product(Vec3D, Vec3D);

Vec3D normalize(Vec3D);


#endif