#include "vops.h"
#include "ray.h"
#include "object.h"
#include "camera.h"
#include "light.h"

// clang render.c camera.c object.c ray.c vmath.c vops.c -lm

int main() {
    int w = 1000, h = 1000;

    Mesh m = read("../objects/icosphere.obj");
    generate_normals(&m);

    OBJ cube = {
        .origin = {0.0, 0.0, 0.0},
        .mesh = m,
        .color = {252, 186, 3}
    };
    OBJ objects[] = {cube};
    int objects_size = sizeof(objects) / sizeof(OBJ);

    Camera cam = initializationCamera(w, h, 90, (Vec3D) {0.0, 0.0, 2.5});
    cam.max_depth = 3;

    Light light1 = {
        .type = 1,
        .position = {1.0, 0.0, 5.0},
        .direction = {0.0, 0.0, 0.0}, 
        .intensity = 0.8
    };
    // Light lights[] = {light1};
    // int lights_size = sizeof(lights) / sizeof(Light);

    ArrayUC image = render(cam, 1, light1, objects, objects_size);
    
    writeArrayToFile(w, h, &image);

    return 0;
}