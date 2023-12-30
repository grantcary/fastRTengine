#include <math.h>
#include "vec.c"

Vec3D vadd(Vec3D a, Vec3D b) {
    return (Vec3D) {a.vec[0] + b.vec[0], a.vec[1] + b.vec[1], a.vec[2] + b.vec[2]};
}

Vec3D vsub(Vec3D a, Vec3D b) {
    return (Vec3D) {a.vec[0] - b.vec[0], a.vec[1] - b.vec[1], a.vec[2] - b.vec[2]};
}

Vec3D cross_product(Vec3D a, Vec3D b) {
    double ux = a.vec[0], uy = a.vec[1], uz = a.vec[2];
    double vx = b.vec[0], vy = b.vec[1], vz = b.vec[2];

    double cx = uy * vz - uz * vy;
    double cy = uz * vx - ux * vz;
    double cz = ux * vy - uy * vx;

    return (Vec3D) {cx, cy, cz};
}

Vec3D normalize(Vec3D v) {
    double vx = v.vec[0], vy = v.vec[1], vz = v.vec[2];
    double magnitude = sqrt(pow(vx, 2.0) + pow(vy, 2.0) + pow(vz, 2.0));
    if (magnitude == 0) {
        return (Vec3D) {0.0, 0.0, 0.0};
    }
    return (Vec3D) {vx / magnitude, vy / magnitude, vz / magnitude};
}