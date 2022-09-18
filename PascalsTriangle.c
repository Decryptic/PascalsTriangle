// Gage Swenson
// 03 July 2022

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isInt(const char *d) {
    for (int i = 0; i < strlen(d); i++) {
        switch(d[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                continue;
        }
        return false;
    }
    return true;
}

int **makeTriangle(const int d) {
    int **triangle = malloc(sizeof(int*) * (d+1));
    triangle[0] = malloc(sizeof(int));
    triangle[0][0] = 1;
    if (d == 0)
        return triangle;
    triangle[1] = malloc(sizeof(int) * 2);
    triangle[1][0] = 1;
    triangle[1][1] = 1;
    for (int i = 2; i < d+1; i++) {
        triangle[i] = malloc(sizeof(int) * (i+1));
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for (int j = 1; j < i; j++)
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
    }
    return triangle;
}

void showTriangle(int **triangle, const int d) {
    for (int i = 0; i < d+1; i++) {
        for (int j = 0; j < d-i; j++)
            printf("\t");
        for (int j = 0; j < i; j++)
            printf("%d\t\t", triangle[i][j]);
        printf("%d\n", triangle[i][i]);
    }
}

void freeTriangle(int **triangle, const int d) {
    for (int i = 0; i < d+1; i++)
        free(triangle[i]);
    free(triangle);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("argc must be greater than 1\n");
        return 1;
    }
    const char *argv1 = argv[1];
    if (!isInt(argv1)) {
        printf("argv[1] must be a positive int\n");
        return 2;
    }
    const int d = atoi(argv1);
    int **triangle = makeTriangle(d);
    showTriangle(triangle, d);
    freeTriangle(triangle, d);
    return 0;
}
