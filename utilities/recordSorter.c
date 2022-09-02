/**
 * This file is a standard implementation of mergesort
 * which uses the type 'record'.
 * 
 * The type 'record' is defined in 'keyValueRecord.h' but can be substituted with any implementation
 * which is named 'record' and has a field 'key' and the type of 'key' supports comparison operations
 * such as <, <=, ==, >=, >, !=
 * Example:
 * struct s_record{
 * 	float key;
 * }; typedef struct s_record record;
 *
 * If the type 'record' is redefined, all the following procedures defined
 * in 'keyValueRecord.h' must be reimplemented:
 *  - record *makeRecord(float key,..);
 *  - record *makeEmptyRecord();
 *  - record *copyAllocateRecord(record *r);
 *  - void copyRecord(record *p,record *r);
 *  - void destroyRecord(record *r);
 * 
 */ 

#include <stdlib.h>
#include <assert.h>
#include "keyValueRecord.h"

void mergeRecord(record **arr, int p, int r, int q){
	int la = r-p+1;
	int lb = q-(r+1)+1;
	int l = q-p+1;
	record **a = (record **)malloc(sizeof(record *)*la);
	record **b = (record **)malloc(sizeof(record *)*lb);

	// a <- arr[p...r]
	for(int i = 0; i < la; i++){
		a[i] = copyAllocateRecord(arr[p+i]);
	}

	// b <- arr[r+1...q]
	for(int i = 0; i < lb; i++){
		b[i] = copyAllocateRecord(arr[r+1+i]);
	}

	int ja = 0;
	int jb = 0;
	for(int j = 0; j < l; j++){
		assert(ja < la || jb < lb);
		record* candidate = makeEmptyRecord();
		if(ja < la && jb < lb){
			if(a[ja]->key < b[jb]->key){
				copyRecord(candidate, a[ja]);
				ja++;
			}else{
				copyRecord(candidate, b[jb]);
				jb++;
			}
		}else if(ja < la){
			copyRecord(candidate, a[ja]);
			ja++;
		}else if(jb < lb){
			copyRecord(candidate, b[jb]);
			jb++;
		}

		copyRecord(arr[p+j],candidate);
		destroyRecord(candidate); candidate=NULL;
	}

	// deleting allocated objects
	for(int i = 0; i < la; i++){destroyRecord(a[i]); a[i] = NULL;}
	for(int i = 0; i < lb; i++){destroyRecord(b[i]); b[i] = NULL;}
	free(a);a = NULL;
	free(b);b = NULL;
}

void mergeSortRecord(record **arr, int p, int q){
	if(p < q){
		int r = (p+q)/2;
		mergeSortRecord(arr,p,r);
		mergeSortRecord(arr,r+1,q);
		mergeRecord(arr, p, r, q);
	}
}