#ifndef UTILITIES_STATISTICSCALCULATOR_H
#define UTILITIES_STATISTICSCALCULATOR_H

/**
 * @param arr the set on which to find the median
 * @param l the length of the set
 * @return the median value the values contained in the set
 * @post the returned value is in the set
 */
float findMedian(float* arr, int l);

/**
 * @param arr the set on which to find the mean
 * @param l the length of the set
 * @return the mean value of the values contained in the set
 */
float findMean(float *arr, int l);

/**
 * @param arr the set on which to find the median
 * @param l the length of the set
 * @param mu the Mean of the values contained in the set
 * @return the standard deviation of the values contained in the set
 */
float findStandardDeviation(float *arr, int l, float mu);


#endif
