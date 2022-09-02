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

void pastePoint(float *p1, float *p2, int dim){
    for(int i = 0; i < dim; i++){
        p1[i] = p2[i];
    }
}

