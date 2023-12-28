#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "vec.c"

typedef struct {
    ArrayD vertices;
    ArrayI faces;
    ArrayD normals;
} Mesh;

typedef struct {
    int origin[3];
    Mesh mesh;
    unsigned char color[3];
} OBJ;

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
                    m.faces.array[f].vec[k++] = faceIndex;
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

int main() {
    char file_name[] = "cube.obj";
    Mesh m = read(file_name);
    return 0;
}