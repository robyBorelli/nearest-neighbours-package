#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "entropyCalculator.h"
#include "sorter.h"
#include "distanceCalculator.h"

// Theta(n) time
void fit1w(float *y,float *x, float *w, int n,float *a,float *sd){
    int i,j,k;
    float xm = 0, ym = 0, x2 = 0, y2 = 0, xy = 0,xy2 = 0,wt = 0,sig2 = 0;
    for(i = 0; i< n; i++){
        xm += x[i]*w[i];
        ym += y[i]*w[i];
        y2 += y[i]*y[i]*w[i];
        x2 += x[i]*x[i]*w[i];
        xy += x[i]*y[i]*w[i];
        xy2 += x[i]*y[i]*x[i]*y[i]*w[i];
        wt += w[i];
    }
    xm /= wt;
    ym /= wt;
    x2 /= wt;
    y2 /= wt;
    xy /= wt;
    xy2 /= wt;
    a[1] = (xy - xm * ym)/(x2 - xm*xm);
    a[0] = ym - a[1] * xm;
    for(i = 0; i< n; i++) {
        sig2 += (y[i] - a[0] - a[1] * x[i]) * (y[i] - a[0] - a[1] * x[i]) * w[i];
    }
    sig2 = sig2/wt;
    sd[0] = sqrt(sig2 * (float) n / (float) (n-2)) * sqrt((1.0/(float) n) + xm*xm/((float) n * (x2 - xm*xm)));
    sd[1] = sqrt(sig2 * (float) n / (float) (n-2)) /  sqrt((float) n *(x2 - xm*xm));
}

// Theta(1) time
float gammln(float xx){
    double x,tmp,ser;
    static double cof[6]={76.18009173,-86.50532033,24.01409822, -1.231739516,0.120858003e-2,-0.536382e-5};
    int j;

    x=xx-1.0;
    tmp=x+5.5;
    tmp -= (x+0.5)*log(tmp);
    ser=1.0;
    for (j=0;j<=5;j++){
        x += 1.0;
        ser += cof[j]/x;
    }
    return -tmp+log(2.50662827465*ser);
}

float calcEntropy(float **points, float ***res, float *lower, float *upper, int d, int m, int n){

    printf("\n\nENTROPY\n");

    int i,j;
    float *a = calloc(3,sizeof(float));
    float *b = calloc(d,sizeof(float));
    float *t = calloc(m,sizeof(float));
    float *dij = calloc(m,sizeof(float));
    float *ldij = calloc(m,sizeof(float));
    float *lkm1 = calloc(m,sizeof(float));
    float *w = calloc(m,sizeof(float));
    float *s = calloc(m,sizeof(float));
    float *sd = calloc(m,sizeof(float));

    for(j = 0; j < m; j++){
        dij[j]=ldij[j]=0.0;
    }
    for(i = 0; i <n; i++){// n * m log m

        for(j = 0; j < m; j++){
            t[j] = periodicDistance(points[i], res[i][j], d);
        }

        mergeSort(t,0,m-1);

        for(j = 0; j < m; j++){
            dij[j] += t[j];
            if(t[j] > 0){
                ldij[j] += log(t[j]);
            }else{
                printf("dist = 0....\n");
            }
        }
    }

    lkm1[0] = 0;
    w[0] = (M_PI)*(M_PI)/6.0;
    for(j = 1; j < m; j++){
        lkm1[j] = lkm1[j-1] + 1/(float) j;
        w[j] = w[j-1] - 1.0/((float) (j*j));
    }
    for(j = 0; j < m; j++){
        dij[j] = dij[j]/ (float) n;
        ldij[j] = ldij[j]/ (float) n;
    }
    for(j = 0; j < m; j++){ // m + 1  corresponds to k of formulas m=0 -> k=1
        s[j] = (float) d * ldij[j] + ((float) d /2.0) *log(M_PI) - gammln((float) d /2.0 + 1.0) + log((float) n) - lkm1[j] + 0.5722  - (float) d * log(360);
    }
    for(j = 0; j < m; j++) {
        printf("%i %f %f\n", j + 1, dij[j], s[j]);
    }

    fit1w(s,dij,w,m,a,sd); // m
    printf("entropy from linear fit: %f\n", a[0]);
    return a[0];
}