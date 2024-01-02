#include <math.h>
#include "vec.c"
#include "vmath.c"

void ray_triangle_intersection(Vec3D origin, Vec3D direction, Vec3D t0, Vec3D t1, Vec3D t2) {
    Vec3D edge1 = vsub(t1, t0), edge2 = vsub(t2, t0);
    Vec3D h = cross_product(direction, edge2);
    double a = dot_product(edge1, h)
;}
