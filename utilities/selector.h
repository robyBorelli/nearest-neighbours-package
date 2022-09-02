#ifndef SELECTOR_H
#define SELECTOR_H

/**
 * @pre p <= i <= q @pre p,q valid indexes for arr
 * @param arr an array with no hypothesis in the distribution
 * @param p start index.
 * @param q end index.
 * @param i an index such that p <= i <= q
 * @return the element arr_2[i] such that arr_2 = sort(arr).
 * Note that the no sorting algorithm is performed and the entire operation takes linear time.
 * @post the computation takes O(q-q)
 * @warning the original order of arr is not preserved
 */
float linearSelect(float *arr,int p,int q,int i);

/**
 * @pre p,q valid indexes for arr
 * @name we call 'x' the value arr[k] before the computation
 * @param arr the array which we want to partition
 * @param p the start index
 * @param q the end index
 * @param k the index of the 'pivot'
 * @return i such that arr[i] = x
 * @post arr is partition around the pivot, in oder words,
 * arr[p...i-1] < x < arr [i+1...q] for some value of i
 */
int partition(float *arr,int p,int q,int k);

/**
 * @pre p,q valid indexes for 'arr'
 * @pre x is present in 'arr'
 * @param arr the array in which we want to search
 * @param p the start index
 * @param q the end index
 * @param x the element we want to search
 * @return on success it is returned the lower i such that arr[i] = x
 * @warning if preconditions are not respected,
 * the function may return -1 and an assertion may be raised
 */
int find(float *arr,int p,int q,float x);

/**
 * @pre p,q valid indexes for arr
 * @param arr the array we want to sort
 * @param p the start index
 * @param q the end index
 * @post arr[p...q] is ordered
 */
void bubbleSort(float *arr,int p,int q);

/**
 * @pre i,j valid indexes for arr
 * @param arr the array on which we perform the swap operation
 * @param i an index for an element arr
 * @param j an index for another element in arr
 * @post arr[i], arr[j] swapped
 */
void swapFloat(float *arr,int i,int j);

#endif
