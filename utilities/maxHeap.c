#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "maxHeap.h"
#include "pointsPrinter.h"

int heapParent(int i){
    return (i - 1) / 2;
}

int heapLeftChild(int i){
    return 2 *i + 1;
}

int heapRightChild(int i){
    return 2 *i + 2;
}

void swapHeapNode(heapNode **x, heapNode **y){
    heapNode* temp = *x;
    *x = *y;
    *y = temp;
}

void heapInsert(heapNode** a, heapNode* data, int *heapLength, int *heapSize){
    if (*heapLength > *heapSize){
        assert(0);
        return;
    }
    a[*heapLength] = data;
    *heapLength = *heapLength + 1;

    int i = *heapLength - 1;
    while (i != 0 && a[heapParent(i)]->distance < a[i]->distance){
        swapHeapNode(& a[heapParent(i)], & a[i]);
        i = heapParent(i);
    }
}

void maxHeapify(heapNode** a, int i, int *heapLength){
    int left = heapLeftChild(i);
    int right = heapRightChild(i);

    int largest = i;
    if (left <= *heapLength && a[left]->distance > a[largest]->distance){
        largest = left;
    }
    if (right <= *heapLength && a[right]->distance > a[largest]->distance){
        largest = right;
    }

    if (largest != i){
        heapNode *temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        maxHeapify(a, largest, heapLength);
    }

}

heapNode* heapMax(heapNode** a){
    return a[0];
}

heapNode* heapDequeue(heapNode** a, int *heapLength){
    heapNode* max_item = a[0];

    a[0] = a[*heapLength - 1];
    *heapLength = *heapLength - 1;

    maxHeapify(a, 0, heapLength);
    return max_item;
}

void printHeap(heapNode** a , int heapLength, int d){
    int i;
    for (i = 0; i < heapLength; i++){
        printPoint(a[i]->point, d);
        printf(":%f ", a[i]->distance);
    }
    printf("\n");
}

heapNode** heapCreate(int size, int *heapSize, int *heapLength){
    heapNode **r = (heapNode**) malloc(sizeof(heapNode*)*size);
    *heapSize = size;
    *heapLength = 0;
    return r;
}

heapNode* heapNodeCreate(float *point, float distance){
    heapNode *r = (heapNode*) malloc(sizeof (heapNode));
    r->distance = distance;
    r->point = point;
    return r;
}

void heapDestroy(heapNode** hn, int hl){
    if(hn != NULL){
        for(int i = 0; i < hl; i++){
            free(hn[i]); hn[i] = NULL;
        }
        free(hn); hn = NULL;
    }
}
