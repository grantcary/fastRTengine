#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vmath.h"
#include "camera.h"

Camera initializationCamera(int w, int h, float fov, Vec3 position) {
    Camera c;
    c.directions.array = malloc(w * h * sizeof(Vec3));
    c.directions.size = w * h;
    c.origins.array = malloc(w * h * sizeof(Vec3));
    c.origins.size = w * h;

    float aspect_ratio = (double) w / h;
    float radians = (fov / 2.0) * (M_PI / 180.0);
    float angle = tan(radians);
    float camera_distance = 1.0 / angle;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float x_normalized = (2 * (x / (float) (w - 1)) - 1) * angle * aspect_ratio;
            float y_normalized = (1 - 2 * (y / (float) (h - 1))) * angle;
            Vec3 ray = {x_normalized, y_normalized, -1.0};
            c.directions.array[(y * w) + x] = normalize(ray);
        }
    }

    for (int i = 0; i < h * w; i++) {
        c.origins.array[i] = position;
    }

    return c;
}