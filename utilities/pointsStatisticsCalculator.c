#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "comparator.h"
#include "selector.h"

float findBestProjectedPoint(float **points, int nPoints, int d, int coordinate, int (*better)(long double, long double)){
    assert(coordinate >= 0 && coordinate < d);
    assert(nPoints >= 0);assert(points != NULL);
    float candidate = points[0][coordinate];
    for(int i = 1; i < nPoints; i++){
        float r = better(points[i][coordinate], candidate);
        if(r == 1){
            candidate = points[i][coordinate];
        }
    }
    return candidate;
}

float findProjectedMedian(float **points, int nPoints, int d, int coordinate){
    assert(coordinate >= 0 && coordinate < d);
    assert(nPoints >= 0);assert(points != NULL);
    float *newArr = (float *)malloc(sizeof(float) * nPoints);
    for(int i = 0; i < nPoints; i++){
        newArr[i] = points[i][coordinate];
    }
    float r = linearSelect(newArr, 0, nPoints-1, nPoints/2);
    free(newArr); newArr = NULL;
    return r;
}

float findProjectedIntervalLength(float **points,int nPoints, int d, int coordinate){
    float max = findBestProjectedPoint(points, nPoints, d,coordinate, strongMaxComparison);
    float min = findBestProjectedPoint(points, nPoints, d,coordinate, strongMinComparison);
    return fabs(max-min);
}