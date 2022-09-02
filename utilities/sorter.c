#include <stdlib.h>
#include <assert.h>

void merge(float *arr, int p, int r, int q){
	int la = r-p+1;
	int lb = q-(r+1)+1;
	int l = q-p+1;
	float *a = (float *)malloc(sizeof(float)*la);
	float *b = (float *)malloc(sizeof(float)*lb);

	// a <- arr[p...r]
	for(int i = 0; i < la; i++){
		a[i] = arr[p+i];
	}

	// b <- arr[r+1...q]
	for(int i = 0; i < lb; i++){
		b[i] = arr[r+1+i];
	}


	int ja = 0;
	int jb = 0;
	for(int j = 0; j < l; j++){
		assert(ja < la || jb < lb);
		float candidate = -1;
		if(ja < la && jb < lb){
			if(a[ja] < b[jb]){
				candidate = a[ja];
				ja++;
			}else{
				candidate = b[jb];
				jb++;
			}
		}else if(ja < la){
			candidate = a[ja];
			ja++;
		}else if(jb < lb){
			candidate = b[jb];
			jb++;
		}

		arr[p+j] = candidate;
	}

	free(a);
	free(b);
}

void mergeSort(float *arr, int p, int q){
	if(p < q){
		int r = (p+q)/2;
		mergeSort(arr,p,r);
		mergeSort(arr,r+1,q);
		merge(arr, p, r, q);
	}
}