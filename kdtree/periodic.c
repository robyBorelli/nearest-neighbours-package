/**
 * @pre q-p+1 = 3^(d-i)
 */
void createImagesSup(float** res, int p, int q, float* delta, int d, int i){
    assert(q-p+1 == pow(3,d-i));
    assert(i < d);
    if(q-p+1 > 3) {
        int l = q - p + 1;
        int m = l / 3;
        assert(3 * m == l);
        int m1 = m + p;
        int m2 = m + m1;
        for(int j = p; j <= m1 - 1; j++){
            sumQtyToThisPointCoordinate(res[j], -delta[i], i, d);
        }
        for(int j = m1; j <= m2 - 1; j++){
            sumQtyToThisPointCoordinate(res[j], 0, i, d);
        }
        for(int j = m2; j <= q; j++){
            sumQtyToThisPointCoordinate(res[j], +delta[i], i, d);
        }

        if(i < d -1) {
            createImagesSup(res, p, m1 - 1, delta, d, i + 1);
            createImagesSup(res, m1, m2 - 1, delta, d, i + 1);
            createImagesSup(res, m2, q, delta, d, i + 1);
        }
    }else if (i < d){
        sumQtyToThisPointCoordinate(res[p], -delta[i], i, d);
        sumQtyToThisPointCoordinate(res[p+1], 0, i, d);
        sumQtyToThisPointCoordinate(res[p+2], +delta[i], i, d);
    }
}

/**
 * @param p is an input point to be shifted
 * @param length is the size of each dimension
 * @param d is the dimensionality
 * @return an array of 3^d - 1 points
 */
float **createImages(float *p, float *length, int d){
    float **res = (float **)malloc(sizeof(float*) * pow(3,d));
    for(int i = 0; i < pow(3,d); i++){
        res[i] = copyPoint(p, d);
    }
    createImagesSup(res,0, pow(3,d)-1, length, d, 0);
    return res;
}

void updateTrueNeighborhood(heapNode *hn){
    if(trueNeighborsLength < m){
        heapInsert(trueNeighbors,hn,
                   &trueNeighborsLength, &trueNeighborsSize);
    }else{
        heapNode *maxDistNode = heapMax(trueNeighbors);
        float maxD = maxDistNode->distance;
        float currentDistance = hn->distance;

        if(currentDistance < maxD){
            heapDequeue(trueNeighbors, &trueNeighborsLength);
            free(maxDistNode); maxDistNode = NULL;
            heapInsert(trueNeighbors,hn,
                       &trueNeighborsLength, &trueNeighborsSize);
        }
    }
}

/**
 * it's the standard visitLeaf but also updates the heap trueNeighbors
 */
void visitPeriodicLeaf(float *x, node* cn){
    assert(cn != NULL && cn->isLeaf == TRUE);
    for(int i = 0; i < cn->nPoints; i++){
        float *p = cn->points[i];
        float currentDistance = euclideanDistance(p, x, d);
        if(heapLength < m && isSamePoint(x,p,d) == FALSE){
            heapInsert(mNeighbors,
                       heapNodeCreate(p, currentDistance),
                       &heapLength, &heapSize
            );
            updateTrueNeighborhood(heapNodeCreate(p, currentDistance));
        }else if(heapLength >= m){
            heapNode *maxDistNode = heapMax(mNeighbors);
            float maxD = maxDistNode->distance;

            if(currentDistance < maxD && isSamePoint(x,p,d) == FALSE){
                heapDequeue(mNeighbors, &heapLength);
                free(maxDistNode); maxDistNode = NULL;
                heapInsert(mNeighbors,
                           heapNodeCreate(p, currentDistance),
                           &heapLength, &heapSize
                );
                updateTrueNeighborhood(heapNodeCreate(p, currentDistance));
            }
        }
    }
}