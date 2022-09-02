#ifndef UTILITIES_POINTSSTATISTICSCALCULATOR_H
#define UTILITIES_POINTSSTATISTICSCALCULATOR_H

/**
 * @pre coordinate >= 0 && coordinate < d
 * @pre nPoints >= 0 && points != NULL
 * @param points the set of points on which to find the best projected point
 * @param nPoints the number of points
 * @param d the number of dimension of each point
 * @param coordinate the coordinate on which the points are projected
 * @param better the function which handles the comparisons
 * @return The points are projected to the specified coordinate, then the projected values are sequentially compared
 * using the specified function and the best value is returned.
 */
float findBestProjectedPoint(float **points, int nPoints, int d, int coordinate, int (*better)(long double, long double));

/**
 * @pre coordinate >= 0 && coordinate < d
 * @pre nPoints >= 0 && points != NULL
 * @param points the set of points on which to find the projected median
 * @param nPoints the number of points
 * @param d the number of dimension of each point
 * @param coordinate the coordinate on which the points are projected
 * @return The points are projected to the specified coordinate, then the median of those values is calculated and returned
 */
float findProjectedMedian(float **points, int nPoints, int d, int coordinate);

/**
 * @pre coordinate >= 0 && coordinate < d
 * @pre nPoints >= 0 && points != NULL
 * @param points the set of points on which to find the projected interval length
 * @param nPoints the number of points
 * @param d the number of dimension of each point
 * @param coordinate the coordinate on which the points are projected
 * @return The points are projected to the specified coordinate, it is then returned the length of
 * the minimum interval on which those values stand
 */
float findProjectedIntervalLength(float **points,int nPoints, int d, int coordinate);

#endif
