#include "keyValueRecord.h"
#include "recordSorter.h"
#include <stdlib.h>

void sortNeighbors(float** points, float ***res, int n, int m, int d, float(*distanceMetric)(float *,float *,int)){
    for(int i = 0; i < n; i++){
        record ** distances = (record **)malloc(sizeof(record *) * m);

        // create a copy of neighbors
        float **tempNeighbors = (float **) malloc(sizeof (float*)*m);
        for(int k = 0; k < m; k++){
            // tempNeighbors[k] = res[i][k]
            tempNeighbors[k] = (float *) malloc(sizeof (float ) * d);
            for(int h = 0; h < d; h++){
                tempNeighbors[k][h] = res[i][k][h];
            }
        }

        // calculating distances
        for(int j = 0; j < m; j++){
            distances[j] = makeRecord(
                    distanceMetric(points[i], tempNeighbors[j], d),
                    j);
        }

        // sorting distances
        mergeSortRecord(distances,0, m-1);

        // writing result
        for(int k = 0; k < m; k++){
            int neighborIndex = distances[k]->value;
            // res[i][k] = tempNeighbors[neighborIndex]
            for(int h = 0; h < d; h++){
                res[i][k][h] = tempNeighbors[neighborIndex][h];
            }
        }

        for(int k = 0; k < m; k++){
            free(tempNeighbors[k]);
            destroyRecord(distances[k]);
        }

        free(distances);
        free(tempNeighbors);
    }
}