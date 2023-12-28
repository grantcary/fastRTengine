#include <stdio.h>
#include <string.h>

const int H = 100;
const int W = 100;

typedef struct {
    double vec[3];
} Vec3D;

typedef struct {
    Vec3D array[H*W];
} ArrayD;

typedef struct {
    unsigned char vec[3];
} Vec3UC;

typedef struct {
    Vec3UC array[H*W];
} ArrayUC;

typedef struct {
    unsigned int vec[3];
} Vec3I;

typedef struct {
    Vec3I array[H*W];
} ArrayI;

void writeArrayToFile(const ArrayUC *arr) {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d %d\n", H, W);

    for (int i = 0; i < H * W; ++i) {
        // fprintf(file, "%lf %lf %lf\n", arr->array[i].vec[0], arr->array[i].vec[1], arr->array[i].vec[2]);
        fprintf(file, "%u %u %u\n", arr->array[i].vec[0], arr->array[i].vec[1], arr->array[i].vec[2]);
    }

    fclose(file);
}