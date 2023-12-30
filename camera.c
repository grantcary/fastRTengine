#include <stdio.h>
#include <math.h>
#include "vec.c"

typedef struct {
    Vec3D position;
    ArrayD origins, directions;
} Camera;

Camera intializeCamera(int h, int w, float fov, Vec3D position) {
    float aspect_ratio = (float) w / h;
    float radians = (fov / 2.0) * (M_PI / 180.0);
    float camera_distance = 1.0 / tan(radians);

    Camera c;
    return c;

}

int main() {
    Camera c = intializeCamera(100, 100, 90, (Vec3D) {0.0, 0.0, 0.0});

    return 0;
}