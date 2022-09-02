#ifndef ENTROPY_CALCULATOR_H
#define ENTROPY_CALCULATOR_H

/**
 * @param points a set of n d-dimensional points
 * @param res the m nearest neighbors for all points
 * @param lower the lower bounds in the space
 * @param upper the upperbounds in the space
 * @param d the number of dimensions
 * @param m the size of the neighborhood
 * @param n the number of points
 * @return the entropy in a space with periodic boundary conditions
 */
float calcEntropy(float **points, float ***res, float *lower, float *upper, int d, int m, int n);

#endif

