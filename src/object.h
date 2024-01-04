#include "vec.h"

#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
    ArrayD vertices;
    ArrayI faces;
    ArrayD normals;
} Mesh;

typedef struct {
    int origin[3];
    Mesh mesh;
    unsigned char color[3];
} OBJ;

Mesh read(char[]);

void generate_normals(Mesh*);

#endif