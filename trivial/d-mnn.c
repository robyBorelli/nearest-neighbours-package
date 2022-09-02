//Given a d-dimensional space, with n points.
//For each point, find the m nearest.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "../utilities/booleanConstants.h"
#include "utils/d-utils.c"
#include "../utilities/selector.h"
#include "../utilities/inputTaker.h"
#include "../utilities/pointsGenerator.h"
#include "../utilities/pointsPrinter.h"
#include "../utilities/distanceCalculator.h"
#include "../utilities/timeTaker.h"
#include "../utilities/timePrinter.h"
#include "../utilities/entropyCalculator.h"
#include "../utilities/neighborsSorter.h"

/*
 * theta n
 * PRE-------------------------------------
 * points  : is an array of d-points
 * d       : is the dimension of each point
 * n       : dimension of the array.
 * i       : i > -1 & i < n. It's the centre of the search
 * m       : number of points to find
 *
 * POST------------------------------------
 * return  : an array containing the m-nearest d-points
 *           to points[i]
 */
float** findNearest(float**points, int n, int d, int m, int i, float(*distanceMetric)(float*, float*, int)){
    float **nearest = (float **)malloc(sizeof(float *) * m);
    float *currentPoint = points[i];

    // calculate vector of distances
    float *distances = calculateDistancesNaive(points, n, d, i, distanceMetric); // d n^2
    // float *distances = calculateDistancesSmart(points, n, d, i, distanceMetric);    // d n (n+1) / 2
    float *distancesCopy = copyArray(distances, 0, n-1);

    // calculate the biggest distance we can accept
    // note that linearSelect modifies the input array
    // so we need to create and pass a copy
    float latestAcceptedDistance = linearSelect(distancesCopy, 0, n-1, m);
    free(distancesCopy);

    // generating result
    int latestPoints = count(distances, n, latestAcceptedDistance);
    int resultIndex = 0;

    // first scan: points with distance less than latestAcceptedDistance
    for(int pointsIndex = 0; pointsIndex < n && resultIndex < m /*- latestPoints*/; pointsIndex++){
        if (pointsIndex != i && distances[pointsIndex] < latestAcceptedDistance){
            nearest[resultIndex] = copyPoint(points[pointsIndex], d);
            resultIndex++;
        }
    }

    // second scan: points with distance equal than latestAcceptedDistance
    for(int pointsIndex = 0; pointsIndex < n && resultIndex < m;pointsIndex++){
        if (pointsIndex != i && distances[pointsIndex] == latestAcceptedDistance){
            nearest[resultIndex] = copyPoint(points[pointsIndex], d);
            resultIndex++;
        }
    }

    free(distances);
    return nearest;
}

float*** solve(float**points, int n, int d, int m){
    float***result = (float ***)malloc(sizeof(float **) * n);
    for (int i = 0; i < n; i ++){
        result[i] = findNearest(points, n, d, m, i, euclideanDistance);
    }
    freeMatrix(n);
    return result;
}

int main(int argc, char **argv)
{
    int n, m, d;
    float **points;
    arguments* mode = (arguments*) malloc(sizeof(arguments));
    if((points = takeInput(argv, argc, &n, &d, &m, mode)) == NULL){
        // n=10000; m=10; d=3;
        // points = generatePoints(n,d,20, FLOAT);
        return 1;
    }

    if(mode->outputMode == TIME){
        long long time = makeTest(solve,points,n,d,m);
        printTime(time);
        return 0;
    }

    float ***result = solve(points, n, d, m);

    if(mode->sortedMode == SORTED){
        sortNeighbors(points,result,n,m,d,euclideanDistance);
    }

    printf("\nDONE\n");
    if(mode->outputMode == VERBOSE) printVerboseNeighbors(result, points, n, m, d);
    if(mode->outputMode == FLAT) printFlatNeighbors(result, d, m, n);  // prints result


    if(mode->entropyMode == TRUE){
        printf("\n\nENTROPY\n");
        printf("not implemented yet");
        return 1;
    }

    return 0;
}
