#include "vec.h"

#ifndef VMATH_H
#define VMATH_H

#define add(a, b) {a.vec[0] * b.vec[0], a.vec[1] * b.vec[1], a.vec[2] * b.vec[2]}
#define sub(a, b) {a.vec[0] - b.vec[0], a.vec[1] - b.vec[1], a.vec[2] - b.vec[2]}
#define mul(a, b) {a.vec[0] * b.vec[0], a.vec[1] * b.vec[1], a.vec[2] * b.vec[2]}
#define div(a, b) {a.vec[0] / b.vec[0], a.vec[1] / b.vec[1], a.vec[2] / b.vec[2]}

#define addc(a, b) {a.vec[0] + b, a.vec[1] + b, a.vec[2] + b}
#define subc(a, b) {a.vec[0] - b, a.vec[1] - b, a.vec[2] - b}
#define mulc(a, b) {a.vec[0] * b, a.vec[1] * b, a.vec[2] * b}
#define divc(a, b) {a.vec[0] / b, a.vec[1] / b, a.vec[2] / b}

#define sum(a) a.vec[0] + a.vec[1] + a.vec[2]

Vec3 cross_product(Vec3, Vec3);

float dot_product(Vec3, Vec3);

Vec3 normalize(Vec3);

#endif