#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

// Returns x-y in nanoseconds
long long subtractTimeSpec (struct timespec *x, struct timespec *y){
	long long resolution;
	resolution = (x->tv_sec - y->tv_sec) * 1000000000 + x->tv_nsec - y->tv_nsec;
	return resolution;
}

// Returns the clock resolution in nanoseconds
long getClockResolution(){
	struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    }while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}

// Performs a test
long long makeTest(
	float*** (*solve)(float**, int , int , int), 
	float**input,
	int n, int d, int m
)
{
	int k = 0;
	double err = 0.00001; // relative max error admited
	struct timespec start = {}, end = {};
	long resolution = getClockResolution();
	long long time = 0;
	long long tmin = resolution * (1/err + 1);
	long long elapsed = 0;

	clock_gettime(CLOCK_MONOTONIC, &start);
	do{	
		clock_gettime(CLOCK_MONOTONIC, &start);		
		float*** r = solve(input,n,d,m);
		clock_gettime(CLOCK_MONOTONIC, &end);
		long long sub = subtractTimeSpec(&end, &start);
		elapsed += sub;
		k++;

		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				free(r[i][j]); r[i][j] = NULL;
			}
			free(r[i]); r[i] = NULL;
		}
		free(r); r=NULL;

	}while(elapsed < tmin);
	time = elapsed/k;

	return time;
}


// TEST.
// float*** solve(float**a, int b, int c, int d, float(*distanceMetric)(float*, float*, int)){
// 	for(int i = 0; i < 1000; i++){
// 		for(int j = 0; j<10000; j++){
// 			int x=i*j;
// 		}
// 	}
// }

// int main(int argc, char const *argv[])
// {
// 	long long k =  makeTest(solve,NULL, 0,0,0);
// 	printf("%llu",k/1000); // prints microseconds
// 	return 0;
// }