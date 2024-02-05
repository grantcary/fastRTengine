#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "vmath.h"
#include "object.h"
#include "camera.h"
#include "light.h"

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

bool intersect(Mesh m, Vec3D origin, Vec3D direction, double *tNear, int *tIndex) {
    bool isect = false;
    for (int j = 0; j < m.faces.size; j++) {
        int a = m.faces.array[j].vec[0], b = m.faces.array[j].vec[1], c = m.faces.array[j].vec[2];
        Vec3D v0 = m.vertices.array[a], v1 = m.vertices.array[b], v2 = m.vertices.array[c];
        double t = INFINITY, u, v;
        if (ray_triangle_intersection(origin, direction, v0, v1, v2, &t, &u, &v) && t < *tNear) {
            *tNear = t;
            *tIndex = j;
            isect = true;
        }
    }
    return isect;
}

bool trace(OBJ *objects, int objects_size, Vec3D origin, Vec3D direction, double *tNear, int *triIndex, OBJ **hitObject) {
    bool isect = false;
    for (int i = 0; i < objects_size; i++) {
        double local_tNear = INFINITY;
        int local_triIndex = -1;
        if (intersect(objects[i].mesh, origin, direction, &local_tNear, &local_triIndex) && local_tNear < *tNear) {
            *tNear = local_tNear;
            *triIndex = local_triIndex;
            *hitObject = &objects[i];
            isect = true;
        }
    }
    return isect;
}

Vec3UC castRay(int ray_depth, Vec3D origin, Vec3D direction, Light light, OBJ *objects, int objects_size) {
    if (ray_depth == 0) {
        return (Vec3UC) {0, 0, 0};
    }

    double tNear = INFINITY;  
    int triIndex = -1;
    OBJ *hitObject = NULL;
    if (trace(objects, objects_size, origin, direction, &tNear, &triIndex, &hitObject)) {
        Vec3D hitPoint = vadd(origin, sdmul(direction, tNear));

        Vec3D lightDir = vsub(light.position, hitPoint);
        double len2 = vsum(vmul(lightDir, lightDir));
        Vec3D normLightDir = svdiv(lightDir, sqrt(len2));

        double tNearShadow = len2;
        int triIndexShadow = -1;
        OBJ *hitObjectShadow = NULL;
        bool inShadow = !trace(objects, objects_size, hitPoint, normLightDir, &tNearShadow, &triIndexShadow, &hitObjectShadow) && pow(tNearShadow, 2) < len2;

        double cosTheta = dot_product((*hitObject).mesh.normals.array[triIndex], normLightDir);
        return sumul((*hitObject).color, light.intensity * (float) fmax(0.0, cosTheta) * (1 - inShadow));
    }
    return (Vec3UC) {127, 127, 127};
}

ArrayUC render(Camera cam, int ray_depth, Light light, OBJ objects[], int objects_size) {
    ArrayUC arr;
    arr.array = malloc(cam.directions.size * sizeof(Vec3UC));
    arr.size = cam.directions.size;

    for (int i = 0; i < cam.directions.size; i++) {
        Vec3D origin = cam.origins.array[i], direction = cam.directions.array[i];
        arr.array[i] = castRay(ray_depth, origin, direction, light, objects, objects_size);
    }
    return arr;
}