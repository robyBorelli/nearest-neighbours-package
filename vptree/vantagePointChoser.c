float* choseRandomVantagePoint(float **points, int nPoints){
    int vpIndex = rand()%nPoints;
    float *vp = copyPoint(points[vpIndex], d);
    return vp;
}

float* choseRandomizedOptimalVantagePoint(float **points, int nPoints){
    int setSize = (int)sqrt(nPoints)/2;
    float ** set1 = choseSet(points, nPoints, setSize);
    float bestSigma = 0;
    float *bestVp = (float *)malloc(sizeof(float)*d);

    for(int i = 0; i < setSize; i++){
        float *vp = set1[i];
        float ** set2 = choseSet(points, nPoints, setSize);
        float *distances = calculatePointDistances(set2, setSize, vp, d, distanceMetric);
        float mu = findMean(distances, setSize);
        float sigma = findStandardDeviation(distances, setSize, mu);

        if(sigma > bestSigma){
            pastePoint(bestVp, vp, d);
            bestSigma = sigma;
        }

        freeSet(set2, setSize);
    }

    freeSet(set1, setSize);
    return bestVp;
}