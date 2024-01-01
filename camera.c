#include <stdio.h>
#include <math.h>
#include "vec.c"

typedef struct {
    Vec3D position;
    ArrayD origins, directions;
} Camera;

void normalize(Vec3D *v) {
    double length = sqrt(v->vec[0] * v->vec[0] + v->vec[1] * v->vec[1] + v->vec[2] * v->vec[2]);
    v->vec[0] /= length;
    v->vec[1] /= length;
    v->vec[2] /= length;
}

Camera initializationCamera(int h, int w, float fov, Vec3D position) {
    Camera c;
    memset(&c, 0, sizeof(c));

    double aspect_ratio = (double) w / h;
    double radians = (fov / 2.0) * (M_PI / 180.0);
    double angle = tan(radians);
    double camera_distance = 1.0 / angle;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            double x_normalized = 2 * (x / (double) (w - 1)) - 1;
            double y_normalized = 2 * (y / (double) (h - 1)) - 1;

            Vec3D ray = {x_normalized * angle * aspect_ratio, y_normalized * angle, camera_distance};
            normalize(&ray);
            c.directions.array[(y * w) + x] = ray;
        }
    }

    for (int i = 0; i < h*w; i++) {
        c.origins.array[i] = position;
    }

    return c;
}

int main() {
    Camera c = initializationCamera(100, 100, 90, (Vec3D) {0.0, 0.0, 0.0});
    return 0;
}