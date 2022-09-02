#include <stdlib.h>
#include <assert.h>
#include <math.h>

void swapFloat(float* arr, int i, int j){
    float temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(float *arr, int p, int q){
    for(int i = p; i <= q; i++){
        for(int j = p; j <= q-1; j++){
            if(arr[j] > arr[j+1]){
                swapFloat(arr, j, j+1);
            }
        }
    }
}

int find(float *arr, int p, int q, float x){
    for (int i = p; i <= q; i++){
        if(arr[i] == x){
            return i;
        }
    }
    assert(0);
    return -1;
}

int partition(float *arr, int p, int q, int k){
    float x = arr[k];  // pivot
    swapFloat(arr, q, k); // place the pivot at the end
    assert(arr[q] == x);

    // invariant
    // arr[p...i]   elements < x
    // arr[i+1...j] elements >= x
    // arr[j+1...q-1] elements not analyzed yet
    int i = p-1;
    for(int j = p; j < q; j++){
        if(arr[j]<x){
            i++;
            swapFloat(arr,i,j);
        }
    }

    i++;
    swapFloat(arr, i, q);
    assert(arr[i] == x);
    return i;
}

float linearSelect(float *arr, int p, int q, int i){
    assert(p <= i && i <= q);

    //0) base case: there are less than 5 elements
    if(q-p+1 < 5){
        bubbleSort(arr,p,q);
        return arr[i];
    }

    //1) dividing in blocks of 5 and finding the median for each block
    int n = ceil((double)(q-p+1) / 5.0);
    float *medians = (float *)malloc(sizeof(float) * n);
    int j;
    for(j = 0; j < n-1; j++){
        assert((5*j)+(5-1)+p <= q);
        bubbleSort(arr, (5*j)+p, (5*j)+(5-1)+p);
        medians[j] = arr[(5*j)+p+2];
    }
    bubbleSort(arr, (5*j)+p, q);
    medians[n-1] = arr[(q + ((5*j)+p))/2];

    //2) finding medians of medians
    int medianPos = floor(n*0.5);
    float M = linearSelect(medians, 0, n-1, medianPos);
    int Mindex = find(arr, p, q, M);
    assert(arr[Mindex] == M);
    free(medians); medians = NULL;

    //3) partition around medians of medians
    int k = partition(arr, p, q, Mindex);

    //4) returns or recursion call
    if (i == k){
        return M;
    }else if(i < k){
        return linearSelect(arr,p,k-1,i);
    }else if(i > k){
        return linearSelect(arr,k+1,q,i);
    }

    assert(0);
    return -1;
}