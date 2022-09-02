#ifndef COMPARATOR_H
#define COMPARATOR_H

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return n1 if n1 > n2, otherwise n2 is returned
 */
long double strongMax(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return n1 if n1 < n2, otherwise n2 is returned
 */
long double strongMin(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return n1 if n1 >= n2, otherwise n2 is returned
 */
long double weakMax(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return n1 if n1 <= n2, otherwise n2 is returned
 */
long double weakMin(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return 1 if n1 > n2, otherwise -1 is returned
 */
int strongMaxComparison(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return 1 if n1 < n2, otherwise -1 is returned
 */
int strongMinComparison(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return 1 if n1 >= n2, otherwise -1 is returned
 */
int weakMaxComparison(long double n1, long double n2);

/**
 * @param n1 first item to compare
 * @param n2 second item to compare
 * @return 1 if n1 <= n2, otherwise -1 is returned
 */
int weakMinComparison(long double n1, long double n2);

#endif