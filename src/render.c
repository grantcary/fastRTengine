#include "vops.h"
#include "ray.h"
#include "object.h"
#include "camera.h"

// clang render.c camera.c object.c ray.c vmath.c vops.c -lm

int main() {
    int w = 100, h = 100;

    Mesh mesh = read("../objects/cube.obj");
    generate_normals(&mesh);

    Camera cam = initializationCamera(w, h, 90, (Vec3D) {0.0, 0.0, 5.0});
    ArrayUC hit = object_intersection_test(cam, mesh);
    
    writeArrayToFile(w, h, &hit);

    return 0;
}