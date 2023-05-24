// define DEBUG_ON constant to see additional output while the kdtree is built
// #define DEBUG_ON

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <limits.h>

// n: number of points
// d: number of dimension
// m: number of buckets
// b: number of points in bucket
int n, m, d, b;
float **records;

#include "../utilities/booleanConstants.h"
#include "../utilities/pointsGenerator.h"
#include "../utilities/pointsPrinter.h"
#include "../utilities/distanceCalculator.h"
#include "../utilities/comparator.h"
#include "../utilities/statisticsCalculator.h"
#include "../utilities/pointsStatisticsCalculator.h"
#include "../utilities/timeTaker.h"
#include "../utilities/timePrinter.h"

#include "points.c"
float (*distanceMetric) (float*, float*, int) = &euclideanDistance;
#include "../utilities/selector.h"
#include "utils.c"
#include "dataTypes.c"
#include "../utilities/maxHeap.h"
heapNode ** mNeighbors = NULL;
int heapSize;
int heapLength;
float tau;

#include "vantagePointChoser.c"
//choseRandomVantagePoint
//choseRandomizedOptimalVantagePoint
float* (*choseVantagePoint) (float**, int) = &choseRandomVantagePoint;
#include "vptree.c"
#include "../utilities/inputTaker.h"
#include "../utilities/entropyCalculator.h"
#include "../utilities/neighborsSorter.h"

float*** solve(float**records, int n, int d, int m){
    float **recordsCopy = (float **)malloc(sizeof(float *) * n);
    for(int i = 0; i < n; i++){recordsCopy[i] = copyPoint(records[i], d);}
    node *root = buildVpTree(recordsCopy, n);
    float ***res = allQueries(root);

    destroyVpTree(root);
    return res;
}

int main(int argc, char **argv){
    b =20;
    arguments* mode = (arguments*) malloc(sizeof(arguments));
    if((records = takeInput(argv, argc, &n, &d, &m, mode)) == NULL){
        // TEST
        // n=10000; m=10; d=3; b=10;
        // records = generatePoints(n, d, 10, FLOAT);
        return 1;
    }

    if(mode->outputMode == TIME){
        long long time = makeTest(solve,records,n,d,m);
        printTime(time);
        return 0;
    }

    float ***res = solve(records,n,d,m);

    if(mode->sortedMode == SORTED){
        sortNeighbors(records,res,n,m,d,distanceMetric);
    }

    printf("\nDONE\n");
    if(mode->outputMode == VERBOSE) printVerboseNeighbors(res, records, n, m, d);
    if(mode->outputMode == FLAT) printFlatNeighbors(res, d, m, n);     // prints result


    if(mode->entropyMode == TRUE){
        printf("\n\nENTROPY\n");
        printf("not implemented yet");
        return 1;
    }

    return 0;
}