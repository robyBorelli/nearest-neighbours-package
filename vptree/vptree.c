node *makeTerminal(float **points, int nPoints){
    node* r = (node *)malloc(sizeof(node));
    r->isLeaf = TRUE;
    r->leftSon = NULL;
    r->rightSon = NULL;
    r->vantagePoint = NULL;
    r->radius = -1;
    r->points = points;
    r->nPoints = nPoints;
    return r;
}

node *makeNonTerminal(float* vantagePoint, float radius, node *left, node *right){
    node* r = (node *)malloc(sizeof(node));
    r->isLeaf = FALSE;
    r->points = NULL;
    r->nPoints = 0;
    r->vantagePoint = vantagePoint;
    r->radius = radius;
    r->leftSon = left;
    r->rightSon = right;
    return r;
}

void destroyVpTree(node *r){
    if(r!=NULL){
        if(r->isLeaf == TRUE){
            for(int i = 0; i < r->nPoints; i++){
                free(r->points[i]); r->points[i]=NULL;
            }
            free(r->points);
            free(r);
        }else{
            destroyVpTree(r->leftSon);
            destroyVpTree(r->rightSon);
            free(r->vantagePoint);
            free(r);
        }
    }
}

node *buildVpTree(float **points, int nPoints){
    if(points == NULL){ return NULL;}
    if(nPoints <= b){return makeTerminal(points, nPoints);}

    float *vp = choseVantagePoint(points, nPoints);
    float *distances = calculatePointDistances(points, nPoints, vp, d, distanceMetric);
    float radius = findMedian(distances, nPoints);

    // a = [a1, a2, a3]     -> a2 -> [a1]    [a2,a3]
    // a = [a1, a2, a3, a4] -> a3 -> [a1,a2] [a3,a4]
    // -> all points greater or equal than partitionValue goes to the right side

    // calculating right and left set
    float **leftPoints = (float **)malloc(sizeof(float *) * nPoints);
    float **rightPoints = (float **)malloc(sizeof(float *) * nPoints);
    int nLeft = 0, nRight = 0;
    for(int i = 0; i < nPoints; i++){
        if (distances[i] < radius) {
            leftPoints[nLeft] = copyPoint(points[i], d);
            nLeft++;
        } else {
            rightPoints[nRight] = copyPoint(points[i], d);
            nRight++;
        }
    }

    if(nLeft == 0 || nRight == 0){
        //assert(nLeft != 0 && nRight != 0);

        // with the chosen vantage point, we can't partition the space.
        // so we just make a leaf

        for(int i = 0; i < nLeft; i++){
            free(leftPoints[i]);
        }
        for(int i = 0; i < nRight; i++){
            free(rightPoints[i]);
        }
        free(leftPoints);
        free(rightPoints);

        return makeTerminal(points, nPoints);
    }
    



    for(int i = 0; i < nPoints; i++){
        free(points[i]);
        points[i] = NULL;
    }
    free(points); points = NULL;
    free(distances);

    return makeNonTerminal(vp,
                           radius,
                           buildVpTree(leftPoints, nLeft),
                           buildVpTree(rightPoints, nRight)
                           );
}

void visitLeaf(float *x, node* cn){
    assert(cn != NULL && cn->isLeaf == TRUE);
    for(int i = 0; i < cn->nPoints; i++){
        float *p = cn->points[i];
        float currentDistance = distanceMetric(p, x, d);
        if(heapLength < m && isSamePoint(x,p,d) == FALSE){
            heapInsert(mNeighbors,
                       heapNodeCreate(p, currentDistance),
                       &heapLength, &heapSize
                       );
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
            }
        }

        if(heapLength == m){
            tau = heapMax(mNeighbors)->distance;
        }
    }
}

/**
 * @param x the query point
 * @param currentNode the node we are visiting
 * @post the global heap contains the m-nearest-points found in the subtree rooted in currentNode
 */
void query(float *x, node *currentNode){
    assert(mNeighbors != NULL);
    if(currentNode->isLeaf == TRUE){
        visitLeaf(x, currentNode);
    }else{
        float dist = distanceMetric(currentNode->vantagePoint, x, d);
        if(dist < currentNode->radius){
            /* if(dist < currentNode->radius + tau){ */ query(x, currentNode->leftSon); /* } */
            if(dist >= currentNode->radius - tau){ query(x, currentNode->rightSon);}
        }else{
            /* if(dist >= currentNode->radius - tau){ */ query(x, currentNode->rightSon); /* } */
            if(dist < currentNode->radius + tau){ query(x, currentNode->leftSon);}
        }
    }
}

float*** allQueries(node *root){
    float ***res = (float ***)malloc(sizeof(float**)*n);
    for(int i = 0; i < n; i++) {
        heapDestroy(mNeighbors, heapLength);
        mNeighbors = heapCreate(m,&heapSize, &heapLength);
        tau = INT_MAX;

        query(records[i], root);
        res[i] = (float **)malloc(sizeof(float *)*m);
        for(int j = 0; j < m && j < heapLength; j++){
            res[i][j] = copyPoint(mNeighbors[j]->point, d);
        }
    }
    return res;
}