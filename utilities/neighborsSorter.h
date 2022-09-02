#ifndef NEIGHBORS_SORTER_H
#define NEIGHBORS_SORTER_H


/**
 * a function to sort by distances the m-neighbors of a set of n points
 * @param points the set of points
 * @param res the neighbors for points. res[i][j] is a m-neighbor for points[i]
 * @param n the number of points
 * @param m the size of the neighborhood
 * @param d the number of dimensions of each point
 * @param distanceMetric the function which handles the distance calculations
 */
void sortNeighbors(float** points, float ***res, int n, int m, int d, float(*distanceMetric)(float *,float *,int));

#endif
