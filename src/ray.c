#include <math.h>
#include "vmath.h"
#include "object.h"
#include "camera.h"

const double EPSILON = 1e-6; 

unsigned ray_triangle_intersection(Vec3D origin, Vec3D direction, Vec3D v0, Vec3D v1, Vec3D v2, double *t, double *u, double *v) {
    Vec3D edge1 = vsub(v1, v0), edge2 = vsub(v2, v0);
    Vec3D pvec = cross_product(direction, edge2);
    double det = dot_product(edge1, pvec);

    if (det < EPSILON || fabs(det) < EPSILON) return 0;

    double invDet = 1.0 / det;
    Vec3D tvec = vsub(origin, v0);
    *u = dot_product(tvec, pvec) * invDet;
    if (*u < 0 || *u > 1) return 0;

    Vec3D qvec = cross_product(tvec, edge1);
    *v = dot_product(direction, qvec) * invDet;
    if (*v < 0 || *u + *v > 1) return 0;

    *t = dot_product(edge2, qvec) * invDet;
    return 1;
}

ArrayUC object_intersection_test(Camera c, Mesh m) {
    ArrayUC arr;
    memset(&arr, 127, sizeof(arr));

    unsigned int count = 0;
    for (int i = 0; i < 100 * 100; i++) {
        Vec3D o = c.origins.array[i], d = c.directions.array[i];
        unsigned y = 0;
        for (int j = 0; m.faces.array[j].vec[0] != 0 || m.faces.array[j].vec[1] != 0 || m.faces.array[j].vec[2] != 0; j++) {
            int a = m.faces.array[j].vec[0], b = m.faces.array[j].vec[1], c = m.faces.array[j].vec[2];
            Vec3D v0 = m.vertices.array[a], v1 = m.vertices.array[b], v2 = m.vertices.array[c];
            double t, u, v;
            unsigned x = ray_triangle_intersection(o, d, v0, v1, v2, &t, &u, &v);
            if (x == 1) {
                y = 1;
            }
            // printf("%u", x);
        }
        if (y == 1) {
            arr.array[i].vec[0] = 255;
            arr.array[i].vec[1] = 255;
            arr.array[i].vec[2] = 255;

            count++;
            printf("%d, %u\n", i, y);
            printf("%lf %lf %lf\n\n", d.vec[0], d.vec[1], d.vec[2]);
            // printf("%lf %lf %lf\n", o.vec[0], o.vec[1], o.vec[2]);
        }

    }
    printf("%d\n", count);
    return arr;
}