#ifndef RENDER_H
#define RENDER_H

#include "vec.h"
#include "object.h"
#include "camera.h"

// ray.c
unsigned ray_triangle_intersection(Vec3D, Vec3D, Vec3D, Vec3D, Vec3D, double*, double*, double*);
ArrayUC object_intersection_test(Camera, Mesh);

// object.c
Mesh read(char[]);
void generate_normals(Mesh*);

// vops.c
void writeArrayToFile(const ArrayUC *);

// vmath.c
Vec3D vadd(Vec3D, Vec3D);
Vec3D vsub(Vec3D, Vec3D);
Vec3D cross_product(Vec3D, Vec3D);
double dot_product(Vec3D, Vec3D);
Vec3D normalize(Vec3D);

// camera.c
Camera initializationCamera(int, int, float, Vec3D);

#endif