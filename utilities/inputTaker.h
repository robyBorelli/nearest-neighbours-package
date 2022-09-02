#ifndef INPUT_TAKER_H
#define INPUT_TAKER_H

#define MAX_NUM_SIZE 35
#define SILENT 10
#define VERBOSE 20
#define FLAT 30
#define TIME 40

#define SORTED 50
#define UNSORTED 60

struct s_arguments{
    int outputMode;
    int sortedMode;
    int inputMode;
    int entropyMode;
    int setLowerBound;
    int setUpperBound;
    float *lowerBounds;
    float *upperBounds;
};
typedef struct s_arguments arguments;

/**
 * This function is responsible to (1) read a file containing some points
 * (2) return the points and all the associated values such as number of points, number of dimensions and some others.
 * @pre The file is specified by argv in the following syntax: <programName inputFile [-in <verbose|silent>] [-out <verbose|flat|time|silent>] [-sort] [-entropy]>
 * @pre The file specified has the following syntax:\n
 * n='nValue' d='dValue' m='mValue' \n
 * [L l1 l2 ... ld \n]
 * [U u1 u2 ... ud \n]
 * p1_1 p1_2 ... p1_d \n
 * p2_1 p2_2 ... p2_d \n
 * ...                \n
 * pn_1 pn_2 ... pn_d \n
 * where pi_j is the j-th coordinate of the i-th point
 * ui is the upper bound for the i-th coordinate
 * li is tle lower bound for the i-th coordinate
 * the 2 rows for lower and upper bounds are optional
 * and they should only be used to specify the periodic boundary conditions if the considered space has those.
 * @param argv an array of 'argc' words which indicates (1) a file to be read (2) the output mode.
 * The correct syntax is the following: <programName inputFile [-in <verbose|silent>] [-out <verbose|flat|time|silent>] [-sort] [-entropy]>
 * where square brackets [ ... ] indicate optional arguments
 * and the vertical line between a|b means that a or b is specified
 * @param argc the number of words in 'argv.'
 * @param n a pointer to a variable which handles the n value.
 * @param d a pointer to a variable which handles the d value.
 * @param m a pointer to a variable which handles the m value.
 * @param mode a pointer to a variable which handles the output mode.
 * @return on SUCCESS an an array of read points is returned, indicating that the file specified
 * by the arguments have been read successfully.
 * On FAIL, 'NULL' is returned, indicating that the input string is not in the right format or the file
 * cannot be read successfully.
 * @post on FAIL, an error message is printed to the standard output.
 * @post on SUCCESS, the following statements are guaranteed: (1) m > 0 (2) d > 0 (3) n > 0 (4) m < n
 * @post on SUCCESS, 'args' contains informations about input and output mode
 * @post on SUCCESS, 'n' contains the number of returned points. on FAIL contains an arbitrary value.
 * @post on SUCCESS, 'd' contains the dimension of each point.on FAIL contains an arbitrary value.
 * @post on SUCCESS, 'm' contains the desired number of neighbors for each point. on FAIL contains an arbitrary value.
 */
float **takeInput(char **argv,int argc,int *n,int *d,int *m, arguments* args);

#endif
