#include <stdio.h>
#include <string.h>

const int H = 100;
const int W = 100;

#define ARRAY_SIZE (H*W)

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

// Vec3D unpack(Vec3D v) {
// }