#include <stdio.h>

const int H = 100;
const int W = 100;

typedef struct {
    float vec[3];
} Vec3;

typedef struct {
    Vec3 array[H*W];
} Array;

int main() {
    Array a;

    // printf("%lu", sizeof(a)/(sizeof(float)*3));
    return 0;
}