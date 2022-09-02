#ifndef POINTS_PRINTER_H
#define POINTS_PRINTER_H

/**
 * @param res an array of of array of points or an array of neighborhoods.
 * res[i] represent a neighborhood, in other words, an array of m-neighbors.
 * res[i][0] ... res[i][m-1] are all the neighbors of some point p_i
 * @param d the dimension of each point
 * @param m m the number of neighbors
 * @param n the number of neighborhoods
 * @post 'res' is sequentially printed to standard output with a space between points
 * and a single space between neighborhoods.
 * No other characters are printed before or after the process.
 * @post the order of 'res' is preserved in the printing process
 */
void printFlatNeighbors(float ***res,int d,int m,int n);

/**
 * @param nearest an array of of array of points.
 * @param points an array of points.
 * @pre for each i in [0,n), for each j in [0,m) nearest[i][j] is
 * is a m-neighbor of points[i]
 * @pre length(points) = length(nearest) && for each i in [0,n) length(nearest[i]) = m  &&
 * for each j in [0,m) length(nearest[i][j]) = d.
 * @param n the number of points
 * @param m the number of neighbors for each point
 * @param d the dimension of each of the point
 * @post points and nearest are sequentially printed to standard output.
 */
void printVerboseNeighbors(float ***nearest,float **points,int n,int m,int d);

/**
 * @param points the points to be printed
 * @param n the number of points
 * @param d the dimension of each of the point
 * @param separator a character which will separe the points from each other
 * @post all the points are sequentially printed to the standard output.
 * After printing the points a '\n' char is printed.
 */
void printPoints(float **points,int n,int d,char separator);

/**
 *
 * @param point the input point
 * @param d the dimension of the point
 * @post point is printed to standard output in the format [point_1, ..., point_d]
 * with no blank spaces after and before printing.
 */
void printPoint(float *point,int d);

#endif
