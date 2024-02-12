#ifndef VEC_H
#define VEC_H

typedef struct {
    float vec[3];
} Vec3;

typedef struct {
    Vec3 *array;
    int size;
} Array;

typedef struct {
    unsigned char vec[3];
} Vec3UC;

typedef struct {
    Vec3UC *array;
    int size;
} ArrayUC;

typedef struct {
    unsigned int vec[3];
} Vec3I;

typedef struct {
    Vec3I *array;
    int size;
} ArrayI;

#endif