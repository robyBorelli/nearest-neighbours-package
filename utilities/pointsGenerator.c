#include <time.h>
#include <stdlib.h>

#include "pointsGenerator.h"

float** generatePoints(int n, int d, float dispersionRate, int mode){
	srand ( clock() );
	rand();
	float **points = (float **)malloc(sizeof(float *) * n);
	for(int i = 0; i < n; i++){
		points[i] = (float *)malloc(sizeof(float) * d);
		for(int j = 0; j < d; j++){
			// integer part
			points[i][j] = rand()% (int)(n*dispersionRate);
			// floating part
			if(mode == FLOAT){
				float f1 = (rand()%(int)(n*dispersionRate))+1;
				float f2 = (rand()%(int)(n*dispersionRate))+1;
				float frac = f1 < f2 ? f1/f2 : f2/f1;
				points[i][j] += frac;
			}
		}
	}
	return points;
}