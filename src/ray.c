#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "vmath.h"
#include "object.h"
#include "camera.h"
#include "light.h"

const float EPSILON = 1e-6; 

bool ray_triangle_intersection(Vec3 origin, Vec3 direction, Vec3 v0, Vec3 v1, Vec3 v2, float *t, float *u, float *v) {
    Vec3 edge1 = (Vec3) sub(v1, v0), edge2 = (Vec3) sub(v2, v0);
    Vec3 pvec = cross_product(direction, edge2);
    float det = dot_product(edge1, pvec);

    if (det < EPSILON || fabs(det) < EPSILON) return false;

    float invDet = 1.0 / det;
    Vec3 tvec = (Vec3) sub(origin, v0);
    *u = dot_product(tvec, pvec) * invDet;
    if (*u < 0 || *u > 1) return false;

    Vec3 qvec = cross_product(tvec, edge1);
    *v = dot_product(direction, qvec) * invDet;
    if (*v < 0 || *u + *v > 1) return false;

    *t = dot_product(edge2, qvec) * invDet;
    return true;
}

bool intersect(Mesh m, Vec3 origin, Vec3 direction, float *tNear, int *tIndex) {
    bool isect = false;
    for (int j = 0; j < m.faces.size; j++) {
        int a = m.faces.array[j].vec[0], b = m.faces.array[j].vec[1], c = m.faces.array[j].vec[2];
        Vec3 v0 = m.vertices.array[a], v1 = m.vertices.array[b], v2 = m.vertices.array[c];
        float t = INFINITY, u, v;
        if (ray_triangle_intersection(origin, direction, v0, v1, v2, &t, &u, &v) && t < *tNear) {
            *tNear = t;
            *tIndex = j;
            isect = true;
        }
    }
    return isect;
}

bool trace(OBJ *objects, int objects_size, Vec3 origin, Vec3 direction, float *tNear, int *triIndex, OBJ **hitObject) {
    bool isect = false;
    for (int i = 0; i < objects_size; i++) {
        float local_tNear = INFINITY;
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

Vec3UC castRay(int ray_depth, Vec3 origin, Vec3 direction, Light light, OBJ *objects, int objects_size) {
    if (ray_depth == 0) {
        return (Vec3UC) {0, 0, 0};
    }

    float tNear = INFINITY;  
    int triIndex = -1;
    OBJ *hitObject = NULL;
    if (trace(objects, objects_size, origin, direction, &tNear, &triIndex, &hitObject)) {
        Vec3 hitPoint = (Vec3) add(origin, (Vec3) mulc(direction, tNear));
        
        if ((*hitObject).material == 0) {  // diffuse

            Vec3 lightDir = (Vec3) sub(light.position, hitPoint);
            float len2 = sum((Vec3) mul(lightDir, lightDir));
            Vec3 normLightDir = (Vec3) divc(lightDir, sqrt(len2));

            float tNearShadow = len2;
            int triIndexShadow = -1;
            OBJ *hitObjectShadow = NULL;
            bool inShadow = !trace(objects, objects_size, hitPoint, normLightDir, &tNearShadow, &triIndexShadow, &hitObjectShadow) && pow(tNearShadow, 2) < len2;

            float cosTheta = dot_product((*hitObject).mesh.normals.array[triIndex], normLightDir);
            return (Vec3UC) mulc((*hitObject).color, light.intensity * (float) fmax(0.0, cosTheta) * (1 - inShadow));
        } else if ((*hitObject).material == 1) { // reflect
            float cosTheta = dot_product((*hitObject).mesh.normals.array[triIndex], direction);
            Vec3 reflectionDirection = (Vec3) sub(direction, (Vec3) mulc((*hitObject).mesh.normals.array[triIndex], cosTheta * 2.0));
            return castRay(ray_depth - 1, hitPoint, reflectionDirection, light, objects, objects_size);
        }
    }
    return (Vec3UC) {127, 127, 127};
}

ArrayUC render(Camera cam, int ray_depth, Light light, OBJ objects[], int objects_size) {
    ArrayUC arr;
    arr.array = malloc(cam.directions.size * sizeof(Vec3UC));
    arr.size = cam.directions.size;

    for (int i = 0; i < cam.directions.size; i++) {
        Vec3 origin = cam.origins.array[i], direction = cam.directions.array[i];
        arr.array[i] = castRay(ray_depth, origin, direction, light, objects, objects_size);
    }
    return arr;
}