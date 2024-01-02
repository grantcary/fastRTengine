#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "render.h"

// void scanArrayForNumbers(char arr[], char *num[]) {
// }

Mesh read(char file_name[]) {
    Mesh m;
    memset(&m, 0, sizeof(m));

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
    fclose(file);
    return m;
}

void generate_normals(Mesh *m) {
    for (int i = 0; m->faces.array[i].vec[0] != 0 || m->faces.array[i].vec[1] != 0 || m->faces.array[i].vec[2] != 0; i++) {
        int a = m->faces.array[i].vec[0], b = m->faces.array[i].vec[1], c = m->faces.array[i].vec[2];
        Vec3D v0 = m->vertices.array[a], v1 = m->vertices.array[b], v2 = m->vertices.array[c];
        Vec3D n = cross_product(vsub(v1, v0), vsub(v2, v0));
        m->normals.array[i] = normalize(n);
    }
}

// int main() {
//     char file_name[] = "cube.obj";
//     Mesh m = read(file_name);
//     generate_normals(&m);

//     for (int i = 0; i < 16; ++i) {
//         printf("%lf %lf %lf\n", m.normals.array[i].vec[0], m.normals.array[i].vec[1], m.normals.array[i].vec[2]);
//         // printf("%d %d %d\n", m.faces.array[i].vec[0], m.faces.array[i].vec[1], m.faces.array[i].vec[2]);
//     }

//     return 0;
// }