//Given a 1-dimensional space, with n points.
//For each point, find the m nearest.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#include "../utilities/booleanConstants.h"
#include "../utilities/keyValueRecord.h"
#include "../utilities/recordSorter.h"
#include "../utilities/inputTaker.h"
#include "../utilities/pointsGenerator.h"
#include "../utilities/pointsPrinter.h"
#include "../utilities/timeTaker.h"
#include "../utilities/timePrinter.h"
#include "utils/1-utils.c"
#include "../utilities/entropyCalculator.h"
#include "../utilities/neighborsSorter.h"
#include "../utilities/distanceCalculator.h"

/*
 * PRE-------------------------------------
 * points  : is an ORDERED array of points
 * n       : dimension of the array
 * i       : i > -1 & i < n. It's the centre of the search
 * m       : number of points to find
 *
 * POST------------------------------------
 * return  : an array containing the m-nearest points
 *           to points[i]
 */
float* findNearest(float*points, int n, int i, int m){
	float *nearest = (float *)malloc(sizeof(float)*m);
	float currentPoint = points[i];

	int resultIndex = 0;
	int rightIndex = i+1;//1
	int leftIndex = i-1;//-1

	for (int j = 1; j <= m; j++){
		int minIndex;
		float dLeft  = distance(points, leftIndex, i, n); assert(dLeft >= 0);
		float dRight = distance(points, rightIndex, i, n); assert(dRight >= 0);
		
		if(dLeft < dRight){
			minIndex = leftIndex;
			leftIndex --;
		}else{
			minIndex = rightIndex;
			rightIndex ++;
		}

		assert(minIndex<n && minIndex>=0);
		nearest[resultIndex] = points[minIndex];
		resultIndex ++;
	}

	return nearest;
}

float** findAllNearest(float*points, int n, int m){
	float**result = (float **)malloc(sizeof(float *) * n);
	for (int i = 0; i < n; i ++){
		result[i] = findNearest(points, n, i, m);
	}
	return result;
}

float*** solve(float**input, int n, int d, int m){
    float *points;
    points = mapPointsToOneDimension(input, n);        // points are 1-dim
    record** records = mapPointsToRecords(points, n);  // original order records
    mergeSortRecord(records, 0, n-1);        // sorted records
    points = mapRecordsToPoints(records, points, n);   // sorted 1-dim points

    float **neighbors = findAllNearest(points, n, m);  // 1-dim neighbors sorted
    int* order = getOriginalOrder(records,n);
    float ***multiDimRes = mapSolutionToMultiDimension(neighbors, n, m);  // multi-dim ordered neighbors
    float ***orderedRes = getOrderedSolution(multiDimRes, order, n, m);       // original order multi-dim neighbors



    // we need to deallocate:
    // points,records,neighbors,order,multidimRes
    free(points); points = NULL;
    free(order); order = NULL;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            free(multiDimRes[i][j]); multiDimRes[i][j] = NULL;
        }
        free(multiDimRes[i]); multiDimRes[i] = NULL;
        free(records[i]); records[i] = NULL;
        free(neighbors[i]); neighbors[i] = NULL;
    }
    free(records);
    free(neighbors);
    free(multiDimRes);

    return orderedRes;
}

int main(int argc, char **argv){
	int n, m, d;
    float** points;

    arguments* mode = (arguments*) malloc(sizeof(arguments));
    if((points = takeInput(argv, argc, &n, &d, &m, mode)) == NULL){
        // TEST
        // n=50; m=10; d=1;
        // input = generatePoints(n,d,20, FLOAT);
        return 1;
    }
    assert(d == 1);

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
    if(mode->outputMode == VERBOSE) printVerboseNeighbors(result, points, n, m, 1);
    if(mode->outputMode == FLAT) printFlatNeighbors(result, 1, m, n);

    if(mode->entropyMode == TRUE){
        printf("\n\nENTROPY\n");
        printf("not implemented yet");
        return 1;
    }


	return 0;
}