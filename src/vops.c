#include <stdio.h>
#include <string.h>
#include "vec.h"

void writeArrayToFile(int w, int h, const ArrayUC *arr) {
    FILE *file = fopen("../utils/data.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d %d\n", w, h);

    for (int i = 0; i < arr->size; ++i) {
        // fprintf(file, "%lf %lf %lf\n", arr->array[i].vec[0], arr->array[i].vec[1], arr->array[i].vec[2]);
        fprintf(file, "%u %u %u\n", arr->array[i].vec[0], arr->array[i].vec[1], arr->array[i].vec[2]);
    }

    fclose(file);
}

// Vec3D unpack(Vec3D v) {
// }