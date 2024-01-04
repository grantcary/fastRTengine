#include <stdio.h>
#include <math.h>
#include "vmath.h"
#include "camera.h"

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
            c.directions.array[(y * w) + x] = normalize(ray);
        }
    }

    for (int i = 0; i < h*w; i++) {
        c.origins.array[i] = position;
    }

    return c;
}