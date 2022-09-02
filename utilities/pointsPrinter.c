#include <stdlib.h>
#include <stdio.h>

void printPointPrimitive(float *point, char i, char f, char s, int d){
    if(point == NULL){
        printf("[NULL]");
        return;
    }
    printf("%c", i);
    for(int i = 0; i < d-1; i++){
        printf("%f%c ", point[i], s);
    }
    printf("%f", point[d-1]);
    printf("%c", f);
}

void printPoint(float *point, int d){
    printPointPrimitive(point, '[', ']', ',', d);
}

void printPoints(float **points, int n, int d, char separator){
    for(int i = 0; i < n; i++){
        printPoint(points[i], d);
        printf("%c", separator);
    }
    printf("\n");
}

void printVerboseNeighbors(float ***nearest, float **points, int n, int m, int d){

    for (int i = 0; i < n; i ++){
        printPoint(points[i], d);
        printf(" -> ");
        printPoints(nearest[i], m, d, ' ');
    }
}

void printFlatNeighbors(float ***res, int d, int m, int n){
    for(int i = 0; i <n; i++){
        for(int j = 0; j < m; j++){
            printPointPrimitive(res[i][j],'\0',' ',' ', d);
        }
    }
}