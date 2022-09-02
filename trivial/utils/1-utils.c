float distance(float* points, int i, int j, int n){
    float dist;
    if( j>=n || j<0 || i>=n || i<0){
        dist = (float)INT_MAX;
    }else{
        dist= fabsf(points[i] - points[j]);
    }
    return dist;
}

float ***getOrderedSolution(float ***res, int *order, int n, int m){
    float ***orderedSol = (float ***)malloc(sizeof(float **)*n);
    for(int i = 0; i <n; i++){
        int ind = order[i];
        orderedSol[i] = (float **)malloc(sizeof(float*)*m);
        for(int j = 0; j < m; j++){
            orderedSol[i][j] = (float *)malloc(sizeof(float)*1);
            orderedSol[i][j][0] = res[ind][j][0];
        }
    }
    return orderedSol;
}

record** mapPointsToRecords(float* points, int n){
    record** records = (record**)malloc(sizeof(record*)*n);
    for(int i = 0; i < n; i++){
        records[i] = makeRecord(points[i], i);
    }
    return records;
}

float* mapRecordsToPoints(record**records, float*points, int n){
    for(int i=0; i <n; i++){
        points[i] = records[i]->key;
    }
    return points;
}

float *mapPointsToOneDimension(float **input, int n){
    float *points = (float *)malloc(sizeof(float) * n);
    for(int i = 0; i < n; i++){
        points[i] = input[i][0];
    }
    return points;
}

int *getOriginalOrder(record** records,int n){
    int* order = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        int j = records[i]->value;
        assert(j<n && j>=0);
        order[j] = i;
    }
    return order;
}

float ***mapSolutionToMultiDimension(float **solution, int n, int m){
    float ***multiDimSol = (float ***)malloc(sizeof(float**)*n);
    for(int i = 0; i < n; i++){
        multiDimSol[i] = (float **)malloc(sizeof(float*)*m);
        for(int j = 0; j < m; j++){
            multiDimSol[i][j] = (float *)malloc(sizeof(float)*1);
            multiDimSol[i][j][0] = solution[i][j];
        }
    }
    return multiDimSol;
}
