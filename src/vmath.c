#include <stdio.h>
#include <math.h>
#include "vec.h"
#include "vmath.h"

Vec3 cross_product(Vec3 a, Vec3 b) {
    float ux = a.vec[0], uy = a.vec[1], uz = a.vec[2];
    float vx = b.vec[0], vy = b.vec[1], vz = b.vec[2];

    float cx = uy * vz - uz * vy;
    float cy = uz * vx - ux * vz;
    float cz = ux * vy - uy * vx;

    return (Vec3) {cx, cy, cz};
}

float dot_product(Vec3 a, Vec3 b) {
    return sum((Vec3) mul(a, b));
}

Vec3 normalize(Vec3 v) {
    float vx = v.vec[0], vy = v.vec[1], vz = v.vec[2];
    float magnitude = sqrt(pow(vx, 2.0) + pow(vy, 2.0) + pow(vz, 2.0));
    if (magnitude == 0) {
        return (Vec3) {0.0, 0.0, 0.0};
    }
    return (Vec3) {vx / magnitude, vy / magnitude, vz / magnitude};
}
