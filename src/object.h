#include "vec.h"

#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
    Array vertices;
    ArrayI faces;
    Array normals;
} Mesh;

typedef struct {
    Vec3 origin;
    Mesh mesh;
    Vec3UC color;
} OBJ;

Mesh read(char[]);

void generate_normals(Mesh*);

#endif