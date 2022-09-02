//pre: p,q valid indexes for arr
//returns a new allocated array containing
//the elements arr[p...q]
float *copyFloatArray(float *arr, int p, int q){
    int n = q-p+1;
    float *ris = (float *)malloc(sizeof(float) * n);
    for(int i = 0; i < n; i++){
        ris[i] = arr[i+p];
    }
    return ris;
}

/**
 * @return an array containing n1 elements of arr
 */
float **choseSet(float **points, int n, int n1){
    assert(n1<=n);
    int diff = n - n1;
    int indexes[n1];
    for(int i = 0; i < n1-diff; i++){
        indexes[i] = i;
    }
    for(int i = n1-diff; i < n1; i++){
        indexes[i] = i + (diff * (rand()%2==0));
    }

    float **res = (float **)malloc(sizeof(float *) * n1);
    for(int i = 0; i < n1; i++){
        res[i] = copyPoint(points[indexes[i]], d);
    }
    return res;
}

void freeSet(float **points, int n){
    if(points != NULL){
        for(int i = 0; i < n; i++) {
            free(points[i]);
            points[i] = NULL;
        }
    }
    free(points);
}