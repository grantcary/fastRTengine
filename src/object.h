#include "vec.h"

#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
    ArrayD vertices;
    ArrayI faces;
    ArrayD normals;
} Mesh;

typedef struct {
    Vec3D origin;
    Mesh mesh;
    Vec3UC color;
} OBJ;

Mesh read(char[]);

void generate_normals(Mesh*);

#endif