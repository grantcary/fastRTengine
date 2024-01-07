#include "vops.h"
#include "ray.h"
#include "object.h"
#include "camera.h"

// clang render.c camera.c object.c ray.c vmath.c vops.c -lm

int main() {
    int w = 100, h = 100;

    Mesh m = read("../objects/cube.obj");
    generate_normals(&m);

    OBJ cube = { .origin = {0.0, 0.0, 0.0}, .mesh = m, .color = {252, 186, 3} };
    OBJ objects[] = {cube};
    int objects_size = sizeof(objects) / sizeof(OBJ);

    Camera cam = initializationCamera(w, h, 90, (Vec3D) {0.0, 0.0, 5.0});
    cam.max_depth = 3;

    ArrayUC hit = object_intersection_test(cam, objects, objects_size);
    
    writeArrayToFile(w, h, &hit);

    return 0;
}