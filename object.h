#include "vec.h"

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
