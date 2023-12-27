#include <stdio.h>

const int DEFAULT_ARR_SIZE = 1000;

struct Vec3 {
    float vec[3];
};



struct array {
    float arr[DEFAULT_ARR_SIZE];
    int size;
};

struct Matrix {
    struct array mat[DEFAULT_ARR_SIZE];
};

void populate(struct array* a) {
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        a->arr[i] = i;
    }
}

void print(struct array* a) {
    for (int i = 0; i < a->size; i++) {
        printf("%f\n", a->arr[i]);
    }
}

int main() {
    struct array a1;
    a1.size = DEFAULT_ARR_SIZE;
    populate(&a1);
    // print(&a1);

    struct Matrix m;
    m.mat[0] = a1;
    float num = m.mat[0].arr[(DEFAULT_ARR_SIZE / 2) - 1];
    printf("%f\n", num);

    // printf("%d\n", a1.size);
    return 0;
}
