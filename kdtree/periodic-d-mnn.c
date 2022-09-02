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
float *upperBounds = NULL, *lowerBounds = NULL;
int done;
float *upperBoundsDist = NULL;
float *lowerBoundsDist = NULL;
float *lengthCoordinate = NULL;

int heapSize, trueNeighborsSize;
int heapLength, trueNeighborsLength;

#include "../utilities/booleanConstants.h"
#include "../utilities/pointsGenerator.h"
#include "../utilities/distanceCalculator.h"
#include "../utilities/pointsPrinter.h"
#include "../utilities/comparator.h"
#include "points.c"
#include "../utilities/selector.h"
#include "../utilities/maxHeap.h"
#include "../utilities/pointsStatisticsCalculator.h"
#include "../utilities/entropyCalculator.h"
#include "../utilities/neighborsSorter.h"
#include "dataTypes.c"
heapNode ** mNeighbors = NULL;
heapNode ** trueNeighbors = NULL;
#include "kdtree.c"
#include "periodic.c"
#include "../utilities/inputTaker.h"
#include "../utilities/timeTaker.h"
#include "../utilities/timePrinter.h"

void initializeGlobalScope(){
    done = FALSE;

    heapDestroy(mNeighbors, heapLength);
    mNeighbors = heapCreate(m, &heapSize, &heapLength);

    free(upperBounds); upperBounds = NULL;
    free(lowerBounds); lowerBounds = NULL;
    lowerBounds = (float *)malloc(sizeof (float) * d);
    upperBounds = (float *)malloc(sizeof (float) * d);
    for(int i = 0; i < d; i++){
        upperBounds[i] = INT_MAX;
        lowerBounds[i] = INT_MIN;
    }
}

/**
 * @param x the query point
 * @param currentNode the node we are visiting
 * @post the global heap contains the m-nearest-points found in the subtree rooted in currentNode
 */
void query(float *x, node *currentNode){
    if(done == TRUE){return;} // the solution is already calculated
    if(currentNode->isLeaf == TRUE) {
        visitPeriodicLeaf(x, currentNode);
        if(ballWithinBounds(x)== TRUE){
            done = TRUE;
        }
        return;
    }

    int disc = currentNode->discriminatorKey;
    float part = currentNode->partitionValue;

    // recursive call on the closer side
    if(x[disc] < part){
        float tempBound = upperBounds[disc];
        upperBounds[disc] = part;
        query(x, currentNode->leftSon);
        upperBounds[disc] = tempBound;
    }else{
        float tempBound = lowerBounds[disc];
        lowerBounds[disc] = part;
        query(x, currentNode->rightSon);
        lowerBounds[disc] = tempBound;
    }

    // recursive call on the opposite side if necessary
    if(done == FALSE) {
        if(x[disc] < part){
            float tempBound = lowerBounds[disc];
            lowerBounds[disc] = part;
            if(boundsOverlapBall(x) == TRUE) {
                query(x, currentNode->rightSon);
            }
            lowerBounds[disc] = tempBound;
        }else{
            float tempBound = upperBounds[disc];
            upperBounds[disc] = part;
            if(boundsOverlapBall(x) == TRUE) {
                query(x, currentNode->leftSon);
            }
            upperBounds[disc] = tempBound;
        }
    }

    if(ballWithinBounds(x) == TRUE){
        done = TRUE;
    }
    return;
}

float*** allQueries(node *root){
    float ***res = (float ***)malloc(sizeof(float**)*n);
    for(int i = 0; i < n; i++) {
        // creating additional heap
        heapDestroy(trueNeighbors, trueNeighborsLength);
        trueNeighbors  = heapCreate(m, &trueNeighborsSize, &trueNeighborsLength);

        // creating images
        float **images = createImages(records[i], lengthCoordinate, d);

        // executing algorithm
        for(int k = 0; k < pow(3,d); k++) {
            initializeGlobalScope();
            query(images[k], root);
        }

        // building result
        res[i] = (float **) malloc(sizeof(float *) * m);
        for (int j = 0; j < m; j++) {
            res[i][j] = copyPoint(trueNeighbors[j]->point, d);
        }

        // deleting images
        for(int k = 0; k < pow(3,d); k++) {
            free(images[k]); images[k] = NULL;
        }
        free(images); images = NULL;
    }
    return res;
}

float*** solve(float**records, int n, int d, int m){
    //note that to change distanceMetric you should touch the global variable
    float **recordsCopy = (float **)malloc(sizeof(float *) * n);
    for(int i = 0; i < n; i++){recordsCopy[i] = copyPoint(records[i], d);}
    node *root = buildKdTree(recordsCopy, n);
    float ***res = allQueries(root);

    destroyKdTree(root);
    return res;
}

int main(int argc, char **argv){
    lengthCoordinate = (float *)malloc(sizeof(float) * d);
    b = 10;

    arguments* mode = (arguments*) malloc(sizeof(arguments));
    if((records = takeInput(argv, argc, &n, &d, &m, mode)) == NULL){
        // TEST
        // n=10000; m=10; d=3; b=10;
        // records = generatePoints(n, d, 10, FLOAT);
        return 1;
    }

    // Periodic conditions
    if(mode->setLowerBound == FALSE){
        lowerBoundsDist = (float*)malloc(sizeof (float)*d);
        for(int i = 0; i < d; i++){
            lowerBoundsDist[i] = findBestProjectedPoint(records,n,d,i,strongMinComparison);
        }
    }else{
        lowerBoundsDist = mode->lowerBounds;
    }
    if(mode->setUpperBound == FALSE){
        upperBoundsDist = (float*)malloc(sizeof (float)*d);
        for(int i = 0; i < d; i++){
            upperBoundsDist[i] = findBestProjectedPoint(records,n,d,i,strongMaxComparison);
        }
    }else{
        upperBoundsDist = mode->upperBounds;
    }
    for(int i = 0; i < d; i++){
        lengthCoordinate[i] = fabsf(upperBoundsDist[i]-lowerBoundsDist[i]);
    }

    if(mode->outputMode == TIME){
        long long time = makeTest(solve,records,n,d,m);
        printTime(time);
        return 0;
    }
    float ***res = solve(records,n,d,m);

    if(mode->sortedMode == SORTED){
        sortNeighbors(records,res,n,m,d,euclideanDistance);
    }

    printf("\nDONE\n");
    if(mode->outputMode == VERBOSE) printVerboseNeighbors(res, records, n, m, d);
    if(mode->outputMode == FLAT) printFlatNeighbors(res, d, m, n);     // prints result

    if(mode->entropyMode == TRUE){
        calcEntropy(records,res,lowerBoundsDist,upperBoundsDist,d,m,n);
    }

    return 0;
}