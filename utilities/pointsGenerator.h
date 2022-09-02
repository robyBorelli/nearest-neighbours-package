#ifndef POINT_GENERATOR_H
#define POINT_GENERATOR_H

#define INT 0
#define FLOAT 1

/**
 * @pre n>0 && d>0 && dispersionRate>0 && (mode = 'FLOAT' || mode = 'INT')
 * @param n the number of points to be generated
 * @param d the number of dimensions of each point
 * @param dispersionRate defines the range on which points are generated.
 * if 'dispersionRate' = d then each coordinates of each points is contained in range [0, d*n]
 * @param mode May be 'INT' or 'FLOAT'.
 * 'mode' = 'FLOAT' => generatedPoints is a subset of R^d
 * 'mode' = 'INT' => generatedPoints is a subset of N^d
 * @return an array of n generated (d-dimensional) points according to 'mode' and 'dispersionRate'.
 */
float **generatePoints(int n,int d,float dispersionRate,int mode);

#endif
