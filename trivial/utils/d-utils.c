#include "../../utilities/distanceCalculator.h"

int count(float *distances, int n, float dist){
    int r = 0;
    for(int i = 0; i < n; i++){
        if(distances[i] == dist){
            r++;
        }
    }
    return r;
}

float *copyArray(float* arr,int p, int q){
    int l = q-p+1;
    float *res = (float *)malloc(sizeof(float)*l);
    for(int i = 0; i < l; i++){
        res[i] = arr[i+p];
    }
    return res;
}

float **matrixOfDistances;
float matrixInitilized = 0;

/*
 * Smartness:
 *  When calculating a distance we save it
 *  ... so if we need that distance more times we just return
 * Complexity:
 *	if distances already calculated Theta(n)
 *	if distances not already calculated Theta(nd)
 */
float *calculateDistancesSmart(float **points, int n, int d, int i, float(*distanceMetric)(float*, float*, int)){
    if(matrixInitilized == 0){
        // matrix not already initialized
        matrixOfDistances = (float **)malloc(sizeof(float *)*n);
        for(int i = 0; i < n; i++){
            matrixOfDistances[i] = (float *)malloc(sizeof(float) * n);
            for(int j = 0; j < n; j++){
                matrixOfDistances[i][j] = -1;
            }
        }
        matrixInitilized = 1;
    }

    float *distances = (float *)malloc(sizeof(float) * n);
    float *currentPoint = points[i];
    for(int j = 0; j < n; j++){
        if(matrixOfDistances[i][j] == -1){
            // the distance has never been calculated
            // so let's calculate it and store it
            float currentDist = distanceMetric(currentPoint, points[j], d);
            matrixOfDistances[i][j] = currentDist;
            matrixOfDistances[j][i] = currentDist;
        }

        distances[j] = matrixOfDistances[i][j];
    }
    return distances;
}

void freeMatrix(int n){
    if(matrixInitilized == 1){
        for(int i = 0; i < n; i++){
            free(matrixOfDistances[i]);
            matrixOfDistances[i] = NULL;
        }
        free(matrixOfDistances);
        matrixOfDistances = NULL;
        matrixInitilized = 0;
    }
    assert("matrix is not initialized");
}

float *copyPoint(float *p, float dim){
    assert(p != NULL);
    float *r = (float *)malloc(sizeof(float)*dim);
    for(int i = 0; i < dim; i++){
        r[i] = p[i];
    }
    return r;
}

/*
 * Complexity: Theta(d)
 */
float *calculateDistancesNaive(float **points, int n, int d, int i, float(*distanceMetric)(float*, float*, int)){

    return calculatePointDistances(points,n,points[i],d,distanceMetric);
}