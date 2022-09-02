#ifndef SORTER_H
#define SORTER_H

/**
 * @pre p,q valid indexes for arr
 * @param arr the array to be ordered
 * @param p the start index of the ordering process
 * @param q the end index of the ordering process
 * @post arr[p...q] is ordered
 */
void mergeSort(float *arr,int p,int q);

/**
 * @pre arr[p...r], arr[r+1...q] are ordered
 * @param arr an array of records
 * @post arr[p...q] is ordered
 */
void merge(float *arr,int p,int r,int q);

#endif
