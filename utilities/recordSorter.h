#ifndef RECORD_SORTER_H
#define RECORD_SORTER_H

/**
 * This file includes definition for mergesort on type 'record'
 * which is defined in the file 'keyValueRecord.h'
 * but can be redefined and the code reused following the instruction in
 * 'recordSorter.c'
 */

/**
 * @pre p,q valid indexes for arr
 * @param arr an array of records
 * @param p the start index of the ordering process
 * @param q the end index of the ordering process
 * @post arr[p...q] is ordered by record.key
 */
void mergeSortRecord(record **arr,int p,int q);

/**
 * @pre arr already have records allocated
 * @pre arr[p...r], arr[r+1...q] are ordered by record.key
 * @param arr an array of records
 * @post arr[p...q] is ordered by record.key
 */
void mergeRecord(record **arr,int p,int r,int q);

#endif
