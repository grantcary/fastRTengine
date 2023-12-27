#include <stdio.h>
#include <string.h>

const int H = 100;
const int W = 100;

typedef struct {
    double vec[3];
} Vec3;

typedef struct {
    Vec3 array[H*W];
} Array;

void writeArrayToFile(const Array *arr) {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d %d\n", H, W);

    for (int i = 0; i < H * W; ++i) {
        fprintf(file, "%lf %lf %lf\n", arr->array[i].vec[0], arr->array[i].vec[1], arr->array[i].vec[2]);
    }

    fclose(file);
}

int main() {
    Array a;
    memset(&a, 0, sizeof(a));
    writeArrayToFile(&a);
    return 0;
}