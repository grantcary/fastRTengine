#include "vops.h"
#include "ray.h"
#include "object.h"
#include "camera.h"

// clang render.c camera.c object.c ray.c vmath.c vops.c -lm

int main() {
    int w = 100, h = 100;

    Mesh m = read("../objects/cube.obj");
    generate_normals(&m);

    OBJ obj = { .origin = {0.0, 0.0, 0.0}, .mesh = m, .color = {252, 186, 3} };

    Camera cam = initializationCamera(w, h, 90, (Vec3D) {0.0, 0.0, 5.0});
    ArrayUC hit = object_intersection_test(cam, obj);
    
    writeArrayToFile(w, h, &hit);

    return 0;
}