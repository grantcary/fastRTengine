#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vmath.h"
#include "object.h"

// void scanArrayForNumbers(char arr[], char *num[]) {
// }

Mesh read(char file_name[]) {
    int currentSizeV = 1000;
    int currentSizeF = 1000;
    Mesh m;
    m.vertices.array = malloc(currentSizeV * sizeof(Vec3));
    m.vertices.size = 0;
    m.faces.array = malloc(currentSizeF * sizeof(Vec3I));
    m.faces.size = 0;

    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        perror("Error opening file");
        return m;
    }

    char line[256];
    int v = 0, f = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            char number[64];
            int j = 0, k = 0;
            for (int i = 2; line[i] != '\0'; i++) {
                if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r') {
                    number[j++] = line[i];
                } 
                if ((line[i] == ' ' || line[i] == '\n' || line[i] == '\r' || line[i+1] == '\0') && j > 0) {
                    if (v >= currentSizeV) {
                        currentSizeV *= 2;
                        m.vertices.array = realloc(m.vertices.array, currentSizeV * sizeof(Vec3));
                    }

                    number[j] = '\0';
                    float af = atof(number);
                    m.vertices.array[v].vec[k++] = af;
                    memset(number, 0, sizeof(number));
                    j = 0;
                }
            }
            v++;

        } else if (line[0] == 'f' && line[1] == ' ') {
            char number[64];
            int j = 0, k = 0;
            for (int i = 2; line[i] != '\0'; i++) {
                if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r') {
                    number[j++] = line[i];
                }
                if ((line[i] == ' ' || line[i] == '\n' || line[i] == '\r' || line[i+1] == '\0') && j > 0) {
                    if (f >= currentSizeF) {
                        currentSizeF *= 2;
                        m.faces.array = realloc(m.faces.array, currentSizeF * sizeof(Vec3I));
                    }

                    number[j] = '\0';
                    int faceIndex = atoi(number);
                    m.faces.array[f].vec[k++] = faceIndex - 1;
                    memset(number, 0, sizeof(number));
                    j = 0;
                }
            }
            f++;
        }
    }
    m.vertices.array = realloc(m.vertices.array, v * sizeof(Vec3));
    m.vertices.size = v;
    m.faces.array = realloc(m.faces.array, f * sizeof(Vec3I));
    m.faces.size = f;

    fclose(file);
    return m;
}

void generate_normals(Mesh *m) {
    int currentSizeN = 1000, i = 0;
    m->normals.array = malloc(currentSizeN * sizeof(Vec3));
    m->normals.size = 0;

    for (; i < m->faces.size; i++) {
        int a = m->faces.array[i].vec[0], b = m->faces.array[i].vec[1], c = m->faces.array[i].vec[2];
        Vec3 v0 = m->vertices.array[a], v1 = m->vertices.array[b], v2 = m->vertices.array[c];
        Vec3 n = cross_product((Vec3) sub(v1, v0), (Vec3) sub(v2, v0));
        if (i >= currentSizeN) {
            currentSizeN *= 2;
            m->normals.array = realloc(m->normals.array, currentSizeN * sizeof(Vec3));
        }
        m->normals.array[i] = normalize(n);
    }
    m->normals.array = realloc(m->normals.array, i * sizeof(Vec3));
    m->normals.size = i;
}

// int main() {
//     char file_name[] = "../objects/cube.obj";
//     Mesh m = read(file_name);
//     generate_normals(&m);

//     for (int i = 0; i < m.vertices.size; ++i) {
//         printf("%lf %lf %lf\n", m.vertices.array[i].vec[0], m.vertices.array[i].vec[1], m.vertices.array[i].vec[2]);
//         // printf("%d %d %d\n", m.faces.array[i].vec[0], m.faces.array[i].vec[1], m.faces.array[i].vec[2]);
//     }

//     return 0;
// }