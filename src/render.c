#include "vops.h"
#include "ray.h"
#include "object.h"
#include "camera.h"

// clang render.c camera.c object.c ray.c vmath.c vops.c -lm

int main() {
    Mesh mesh = read("../objects/cube.obj");
    generate_normals(&mesh);

    Camera cam = initializationCamera(100, 100, 90, (Vec3D) {0.0, 0.0, 5.0});
    // for (int i = 0; i < 100 * 100; i++) {
    //     Vec3D v = cam.directions.array[i];
    //     printf("%lf %lf %lf\n", v.vec[0], v.vec[1], v.vec[2]);
    // }

    ArrayUC hit = object_intersection_test(cam, mesh);
    writeArrayToFile(&hit);

    return 0;
}