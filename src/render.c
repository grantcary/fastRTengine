#include "vops.h"
#include "ray.h"
#include "object.h"
#include "camera.h"
#include "light.h"

// clang render.c camera.c object.c ray.c vmath.c vops.c -lm

int main() {
    int w = 1000, h = 1000;

    Mesh c = read("../objects/cube.obj");
    generate_normals(&c);
    OBJ cube = {
        .origin = {0.0, 1.0, 3.0},
        .mesh = c,
        .color = {252, 186, 3},
        .material = 0
    };

    Mesh i = read("../objects/icosphere.obj");
    generate_normals(&i);
    OBJ icosphere = {
        .origin = {0.0, 0.0, 0.0},
        .mesh = i,
        .color = {252, 186, 3},
        .material = 1
    };

    OBJ objects[] = {icosphere};
    int objects_size = sizeof(objects) / sizeof(OBJ);

    Camera cam = initializationCamera(w, h, 90, (Vec3) {0.0, 0.0, 2.5});
    cam.max_depth = 3;

    Light light1 = {
        .type = 1,
        .position = {1.0, 0.0, 5.0},
        .direction = {0.0, 0.0, 0.0}, 
        .intensity = 0.8
    };
    // Light lights[] = {light1};
    // int lights_size = sizeof(lights) / sizeof(Light);

    ArrayUC image = render(cam, 3, light1, objects, objects_size);
    
    writeArrayToFile(w, h, &image);

    return 0;
}