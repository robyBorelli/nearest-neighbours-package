#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include "selector.h"

float findMedian(float* arr, int l){
    float *arrCopy = (float *) malloc(sizeof (float)*l);
    for(int i = 0; i < l; i++){
        arrCopy[i] = arr[i];
    }
    float r = linearSelect(arrCopy, 0, l-1, l/2);
    free(arrCopy); arrCopy=NULL;
    return r;
}

float findMean(float *arr, int l){
    long double res = 0;
    for(int i = 0; i < l; i++){
        res += (long double)arr[i];
    }
    res = res / l;
    return (float) res;
}
float findStandardDeviation(float *arr, int l, float mu){
    long double res = 0;
    for(int i = 0; i < l; i++){
        res += pow(arr[i] - mu, 2);
    }
    res = res / l;
    res = sqrtl(res);
    return (float) res;
}
