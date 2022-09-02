node *makeTerminal(float **points, int nPoints){
    node* r = (node *)malloc(sizeof(node));
    r->isLeaf = TRUE;
    r->leftSon = NULL;
    r->rightSon = NULL;
    r->discriminatorKey = -1;
    r->partitionValue = INT_MAX;
    r->points = points;
    r->nPoints = nPoints;
    return r;
}

node *makeNonTerminal(int discriminator, float partitionValue, node *left, node *right){
    node* r = (node *)malloc(sizeof(node));
    r->isLeaf = FALSE;
    r->points = NULL;
    r->nPoints = 0;
    r->partitionValue = partitionValue;
    r->discriminatorKey = discriminator;
    r->leftSon = left;
    r->rightSon = right;
    return r;
}

void destroyKdTree(node *r){
    if(r!=NULL){
        if(r->isLeaf == TRUE){
            for(int i = 0; i < r->nPoints; i++){
                free(r->points[i]); r->points[i]=NULL;
            }
            free(r->points);
            free(r);
        }else{
            destroyKdTree(r->leftSon);
            destroyKdTree(r->rightSon);
            free(r);
        }
    }
}

node *buildKdTree(float **points, int nPoints){
    if(points == NULL) return NULL;
    if(nPoints <= b){return makeTerminal(points, nPoints);}

    int discriminator = 0;
    float maxSpread = 0, partitionValue = 0;

    for(int j = 0; j < d; j++){
        float currentSpread = findProjectedIntervalLength(points, nPoints, d,j);
        if( currentSpread >= maxSpread){
            maxSpread = currentSpread;
            discriminator = j;
        }
    }

    partitionValue = findProjectedMedian(points,nPoints,d,discriminator);
    // a = [a1, a2, a3]     -> a2 -> [a1]    [a2,a3]
    // a = [a1, a2, a3, a4] -> a3 -> [a1,a2] [a3,a4]
    // -> all points greater or equal than partitionValue goes to the right side

    // calculating right and left set
    float **leftPoints = (float **)malloc(sizeof(float *) * nPoints);
    float **rightPoints = (float **)malloc(sizeof(float *) * nPoints);
    int nLeft = 0, nRight = 0;
    for(int i = 0; i < nPoints; i++){
        if(points[i][discriminator] < partitionValue){
            leftPoints[nLeft] = copyPoint(points[i], d);
            nLeft++;
        }else{
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

    return makeNonTerminal(discriminator,
                           partitionValue,
                           buildKdTree(leftPoints, nLeft),
                           buildKdTree(rightPoints, nRight)
                           );
}

// check if the ball centered in X is fully contained in the bounds of
// the current node
int ballWithinBounds(float *x){
    for(int i = 0; i < d; i++){
        if (x[i] >= upperBounds[i] || x[i] <= lowerBounds[i])
            return FALSE;
    }

    if(heapLength < m){
        return FALSE;
    }

    // ball centered at x and radius neighbors[m]
    float r = heapMax(mNeighbors)->distance;
    for(int i = 0; i < d; i++){
        if(r >= fabsf(x[i] -lowerBounds[i]) ||
        r >= fabsf(x[i] - upperBounds[i])
        ){
            return FALSE;
        }
    }
    return TRUE;
}
int boundsOverlapBall(float *x){
    if(heapLength < m){
        return TRUE;
    }

    float minDistFromBounds = 0;
    float r = heapMax(mNeighbors)->distance;
    for(int i = 0; i < d; i++){
        if(x[i] < lowerBounds[i]){
            minDistFromBounds += pow(x[i] - lowerBounds[i], 2);
            if(sqrt(minDistFromBounds) > r) {return FALSE;}
            // if the min distance x-bounds is GREATER than the radius of the ball -> NO overlap
            if(sqrt(minDistFromBounds) > r) {return FALSE;}

        }else if( x[i] > upperBounds[i]){
            minDistFromBounds += pow(x[i] - upperBounds[i], 2);
            // if the min distance x-bounds is GREATER than the radius of the ball -> NO overlap
            if(sqrt(minDistFromBounds) > r) {return FALSE;}
        }
    }

    //if x is fully contained in bounds
    //minDistFromBounds will be 0
    if(sqrt(minDistFromBounds) <= r){
        // the min distance x-bounds is less than the radius of the ball
        // there is overlap
        return TRUE;
    }else{
        // the min distance x-bounds is GREATER than the radius of the ball
        // there is NO overlap
        assert(ballWithinBounds(x) == FALSE);
        return FALSE;
    }
}

void visitLeaf(float *x, node* cn){
    assert(cn != NULL && cn->isLeaf == TRUE);
    for(int i = 0; i < cn->nPoints; i++){
        float *p = cn->points[i];
        float currentDistance = euclideanDistance(p, x, d);
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
    }
}