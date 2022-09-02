#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

/**
 * @pre length(points) = n && for each i, length(points[i]) = d = length(p)
 * @param points an array of n d-dimensional points.
 * @param n the number of points.
 * @param p a d-dimensional point. May or may not be an element of the input array 'points'.
 * @param d the number of coordinates.
 * @param distanceMetric a function which handles the distance calculation.
 * May be 'euclideanDistance' or 'periodicDistance'.
 * @return an array 'res' of length n. For each i res[i] = distanceMetric(points[i], p).
 */
float *calculatePointDistances(float **points,int n,float *p,int d,float(*distanceMetric)(float *,float *,int));

/**
 * @pre length(a) = length(b) = d && a != NULL && b != NULL.
 * @param a a d-dimensional point.
 * @param b a d-dimensional point.
 * @param d the number of coordinates.
 * @return the euclidean distance in the space R^d.
 */
float euclideanDistance(float *a,float *b,int d);

/**
 * @pre length(a) = length(b) = d && a != NULL && b != NULL.
 * @pre the function 'calculateBoundaries' has already been called.
 * @param a a d-dimensional point.
 * @param b a d-dimensional point.
 * @param d the number of coordinates.
 * @return the distance between a and b in a periodic space already initialized
 * with respective boundaries.
 */
float periodicDistance(float *a,float *b,int d);

/**
 * It's equivalent to periodicDistance. It's just another implementation
 * @pre length(a) = length(b) = d && a != NULL && b != NULL.
 * @pre the function 'calculateBoundaries' has already been called.
 * @param a a d-dimensional point.
 * @param b a d-dimensional point.
 * @param d the number of coordinates.
 * @return the distance between a and b in a periodic space already initialized
 * with respective boundaries.
 */
float periodicDistance2(float *a, float *b, int d);

/**
 * @pre length(low) = length(high) = d && low != NULL && high && NULL.
 * @post the boundaries of the space with periodic conditions
 * have been initialized. The function 'periodicDistance' may be invoked..
 * @param low the lower boundaries of the space for each coordinate.
 * @param high the upper boundaries of the space for each coordinate.
 * @param d the number of coordinates.
 */
void calculateBoundaries(float *low,float *high,int d);

#endif