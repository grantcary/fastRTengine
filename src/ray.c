#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "vmath.h"
#include "object.h"
#include "camera.h"

const double EPSILON = 1e-6; 

bool ray_triangle_intersection(Vec3D origin, Vec3D direction, Vec3D v0, Vec3D v1, Vec3D v2, double *t, double *u, double *v) {
    Vec3D edge1 = vsub(v1, v0), edge2 = vsub(v2, v0);
    Vec3D pvec = cross_product(direction, edge2);
    double det = dot_product(edge1, pvec);

    if (det < EPSILON || fabs(det) < EPSILON) return false;

    double invDet = 1.0 / det;
    Vec3D tvec = vsub(origin, v0);
    *u = dot_product(tvec, pvec) * invDet;
    if (*u < 0 || *u > 1) return false;

    Vec3D qvec = cross_product(tvec, edge1);
    *v = dot_product(direction, qvec) * invDet;
    if (*v < 0 || *u + *v > 1) return false;

    *t = dot_product(edge2, qvec) * invDet;
    return true;
}

bool intersect(Mesh m, Vec3D origin, Vec3D direction, double *tNear) {
    bool isect = false;
    for (int j = 0; j < m.faces.size; j++) {
        int a = m.faces.array[j].vec[0], b = m.faces.array[j].vec[1], c = m.faces.array[j].vec[2];
        Vec3D v0 = m.vertices.array[a], v1 = m.vertices.array[b], v2 = m.vertices.array[c];
        double t = INFINITY, u, v;
        if (ray_triangle_intersection(origin, direction, v0, v1, v2, &t, &u, &v) && t < *tNear) {
            *tNear = t;
            isect |= true;
        }
    }
    return isect;
}

Vec3UC test_objects(Vec3D origin, Vec3D direction, OBJ objects[], int objects_size) {
    double oNear = INFINITY;
    bool isect = false;
    int oIndex = -1;
    for (int j = 0; j < objects_size; j++) {
        double tNear = INFINITY;
        isect |= intersect(objects[j].mesh, origin, direction, &tNear);
        if (tNear < oNear) {
            oNear = tNear;
            oIndex = j;
        }
    }
    if (isect) {
        return objects[oIndex].color;
    }
    return (Vec3UC) {127, 127, 127};
}

ArrayUC object_intersection_test(Camera cam, OBJ objects[], int objects_size) {
    ArrayUC arr;
    arr.array = malloc(cam.directions.size * sizeof(Vec3UC));
    arr.size = cam.directions.size;

    for (int i = 0; i < cam.directions.size; i++) {
        Vec3D origin = cam.origins.array[i], direction = cam.directions.array[i];
        arr.array[i] = test_objects(origin, direction, objects, objects_size);
    }
    return arr;
}