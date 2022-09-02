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

int heapSize;
int heapLength;

#include "../utilities/booleanConstants.h"
#include "../utilities/pointsPrinter.h"
#include "../utilities/distanceCalculator.h"
#include "../utilities/pointsGenerator.h"
#include "../utilities/comparator.h"
#include "points.c"
#include "../utilities/selector.h"
#include "../utilities/maxHeap.h"
#include "../utilities/pointsStatisticsCalculator.h"
#include "../utilities/entropyCalculator.h"
#include "assert.h"
#include "dataTypes.c"
heapNode ** mNeighbors = NULL;
#include "kdtree.c"
#include "../utilities/inputTaker.h"
#include "../utilities/timeTaker.h"
#include "../utilities/timePrinter.h"
#include "../utilities/neighborsSorter.h"

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
        visitLeaf(x, currentNode);
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
        initializeGlobalScope();
        query(records[i], root);

        res[i] = (float **)malloc(sizeof(float *)*m);
        for(int j = 0; j < m; j++){
            res[i][j] = copyPoint(mNeighbors[j]->point, d);
        }
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
    b = 10;

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
        sortNeighbors(records,res,n,m,d,euclideanDistance);
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