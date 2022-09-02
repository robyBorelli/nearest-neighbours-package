int isSamePoint(float *a, float *b, int d){
    if(a == NULL || b == NULL) return FALSE;
    for(int i = 0; i < d; i++){
        if(a[i] != b[i]){
            return FALSE;
        }
    }
    return TRUE;
}

float *copyPoint(float *p, float dim){
    assert(p != NULL);
    float *r = (float *)malloc(sizeof(float)*dim);
    for(int i = 0; i < dim; i++){
        r[i] = p[i];
    }
    return r;
}

void sumQtyToThisPointCoordinate(float *p, float qty, int coordinate, int d){
    assert(coordinate < d);
    assert(coordinate >= 0);
    p[coordinate] += qty;
}