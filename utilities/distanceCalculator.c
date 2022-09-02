#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

float *l = NULL;

void calculateBoundaries(float*low, float* high, int d){
    if(l != NULL){free(l);}

    l = (float *)malloc(sizeof (float)*d);
    for(int i = 0; i < d; i++) {
        l[i] = (float)fabsf(high[i] - low[i]);
    }
}

float periodicDistance(float* a, float* b, int d){
    long double dist=0;
    assert(l != NULL);
    for (int i = 0; i < d ; i++){
        long double d1 = pow(a[i]-b[i], 2);
        long double d2 = pow(a[i]- (b[i]-l[i]), 2);
        long double d3 = pow(a[i]- (b[i]+l[i]), 2);
        long double di = d1;
        if(d2 < di){di = d2;}
        if(d3 < di){di = d3;}

        dist += di;
    }
    dist = sqrtl(dist);
    return (float)dist;
}

float periodicDistance2(float *a, float *b, int d){
    long double dist = 0, t = 0;
    for(int i = 0; i <d; i++){
        t = a[i]-b[i];
        if(t > l[i]/2.0){
            t -= l[i];
        }else if(t < -l[i]/2.0){
            t += l[i];
        }
        dist += t*t ;
    }
    dist = sqrtl(dist);
    return (float)dist;
}

float euclideanDistance(float* a, float* b, int d){
    long double dist=0;
    for (int i = 0; i < d ; i++){
        dist += pow(a[i] - b[i],2);
    }
    dist = sqrtl(dist);
    return (float)dist;
}

float *calculatePointDistances(float **points, int n, float *p, int d, float(*distanceMetric)(float*, float*, int)){
    float *distances = (float *)malloc(sizeof(float) * n);
    for(int j = 0; j < n; j++){
        distances[j] = distanceMetric(p, points[j], d);
    }
    return distances;
}
