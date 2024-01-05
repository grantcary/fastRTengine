#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vmath.h"
#include "camera.h"

Camera initializationCamera(int w, int h, float fov, Vec3D position) {
    Camera c;
    c.directions.array = malloc(w * h * sizeof(Vec3D));
    c.directions.size = w * h;
    c.origins.array = malloc(w * h * sizeof(Vec3D));
    c.origins.size = w * h;

    double aspect_ratio = (double) w / h;
    double radians = (fov / 2.0) * (M_PI / 180.0);
    double angle = tan(radians);
    double camera_distance = 1.0 / angle;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double x_normalized = (2 * (x / (double) (w - 1)) - 1) * angle * aspect_ratio;
            double y_normalized = (1 - 2 * (y / (double) (h - 1))) * angle;
            Vec3D ray = {x_normalized, y_normalized, -1.0};
            c.directions.array[(y * w) + x] = normalize(ray);
        }
    }

    for (int i = 0; i < h * w; i++) {
        c.origins.array[i] = position;
    }

    return c;
}