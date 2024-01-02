#include <stdio.h>
#include <string.h>

#ifndef VEC_H
#define VEC_H

#define ARRAY_SIZE 10000

typedef struct {
    double vec[3];
} Vec3D;

typedef struct {
    Vec3D array[ARRAY_SIZE];
} ArrayD;

typedef struct {
    unsigned char vec[3];
} Vec3UC;

typedef struct {
    Vec3UC array[ARRAY_SIZE];
} ArrayUC;

typedef struct {
    unsigned int vec[3];
} Vec3I;

typedef struct {
    Vec3I array[ARRAY_SIZE];
} ArrayI;

#endif