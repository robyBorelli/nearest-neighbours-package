#ifndef TIME_TAKER_H
#define TIME_TAKER_H
/**
 * @brief measure the performance of a neighborhood algorithm
 * @param solve a function which solves the neighborhood problem
 * @param input a set of input points
 * @param n the number of points
 * @param d the dimension of the points
 * @param m the size of the neighborhood
 * @return the time (in nanoseconds) taken by the computation <solve(input)>.
 * The time measured has a relative error of 0.00001.
 */
long long makeTest(
	float*** (*solve)(float**, int , int , int), 
	float**input,
	int n, int d, int m
);

#endif