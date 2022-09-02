#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "inputTaker.h"
#include "booleanConstants.h"
#include "pointsPrinter.h"

int checkParameters(int n, int d, int m){
    if(n <= 0 || d <= 0 || m <= 0){
        return FALSE;
    }
    if(m >= n){
        return FALSE;
    }
    return TRUE;
}

float *readPoint(FILE *f, int d){
    char line [MAX_NUM_SIZE * d + d]; // a number can have max length
                                      // of MAX_NUM_SIZE
    fscanf(f,"%[^\n]s", line);
    float *p = (float *)malloc(sizeof (float) *d);
    int s = -1;
    int offset = 0;
    int ch = 0;
    for(int i = 0; i < d; i++){
        long double myD;
        s += sscanf(line + offset,"%Le%n", &myD, &ch);
        p[i] = (float)myD;
        if(s != i){return FALSE;}
        offset += ch;
    }
    return p;
}

void printCorrectInvocation(char **argv){
    printf("Correct invocation: <%s inputFile [-in <verbose|silent>] [-out <verbose|flat|time|silent>] [-sort] [-entropy]>\n", argv[0]);
    printf("By default input and output mode are verbose, the neighbors aren't sorted and the entropy is not calculated.\n");
}

float **takeInput(char **argv, int argc, int *n, int *d, int *m, arguments* args){
    int terminateProgram, inputModeSet, outputModeSet, sortedModeSet, entropyModeSet;
    terminateProgram = inputModeSet = outputModeSet = sortedModeSet = entropyModeSet = FALSE;

    // DEFAULT ARGUMENTS
    args->inputMode = VERBOSE;
    args->outputMode = VERBOSE;
    args->sortedMode = UNSORTED;
    args->entropyMode = FALSE;
    args->setLowerBound = args->setUpperBound = FALSE;
    args->lowerBounds = args->upperBounds = NULL;

    if(argc > 8 || argc < 2){
        printCorrectInvocation(argv);
        return NULL;
    }

    // LINE COMMAND PARSER
    for(int i = 2; i < argc; i++){
        if (strncmp(argv[i],"-in", 3) == 0 && inputModeSet == FALSE){
            if(i+1 < argc){
                i++;
                if(strncmp(argv[i],"silent", 6) == 0){
                    args->inputMode = SILENT;
                }else if (strncmp(argv[i],"verbose", 7) == 0){
                    args->inputMode = VERBOSE;
                }else{
                    terminateProgram = TRUE; break;
                }
            }else{
                terminateProgram = TRUE; break;
            }
            inputModeSet=TRUE;
        }else if (strncmp(argv[i],"-out", 4) == 0 && outputModeSet == FALSE){
            if(i+1 < argc){
                i++;
                if(strncmp(argv[i],"silent", 6) == 0){
                    args->outputMode = SILENT;
                }else if (strncmp(argv[i],"verbose", 7) == 0){
                    args->outputMode = VERBOSE;
                }else if (strncmp(argv[i],"flat", 4) == 0){
                    args->outputMode = FLAT;
                }else if (strncmp(argv[i],"time", 4) == 0){
                    args->outputMode = TIME;
                }else{
                    terminateProgram = TRUE; break;
                }
            }else{
                terminateProgram = TRUE; break;
            }
            outputModeSet=TRUE;
        }else if (strncmp(argv[i],"-sort", 5) == 0 && sortedModeSet == FALSE){
            sortedModeSet = TRUE;
            args->sortedMode = SORTED;
        }else if (strncmp(argv[i],"-entropy", 8) == 0 && entropyModeSet == FALSE){
            entropyModeSet = TRUE;
            args->entropyMode = TRUE;
        }else{
            terminateProgram = TRUE; break;
        }
    }

    if(terminateProgram == TRUE){
        printCorrectInvocation(argv);
        return NULL;
    }

    // FILE PARSER
    char *fileName = argv[1];
    FILE *inputFile = fopen(fileName, "r");

    if(inputFile == NULL) {
        printf("Unable to read file %s>\n", fileName);
        return NULL;
    }
    int readItem = fscanf(inputFile, "n=%d d=%d m=%d\n", n, d, m);
    if(readItem != 3 || checkParameters(*n,*d,*m) == FALSE){
        printf("File %s is not in the correct format. Incorrect header found.\n", fileName);
        return NULL;   
    }

    int lines=*n;
    int lineIndex=0, pointIndex = 0;

    float **points = (float **)malloc(sizeof (float *) * (*n));
    for(lineIndex = 0; lineIndex < lines; lineIndex++){

        int readL = 0, readU=0;
        fscanf(inputFile, "L%n", &readL);
        fscanf(inputFile, "U%n", &readU);
        if(readL == 1 && args->setLowerBound == FALSE){
            fscanf(inputFile," ");
            args->lowerBounds = readPoint(inputFile,*d);
            if (args->lowerBounds == NULL){
                printf("File %s is not in the correct format. Incorrect lowerbound found at line %d\n"
                       ,fileName, lineIndex + 2); return NULL;
            }
            lines++;
            args->setLowerBound = TRUE;
        }else if(readU == 1 && args->setUpperBound == FALSE){
            fscanf(inputFile," ");
            args->upperBounds = readPoint(inputFile,*d);
            if (args->upperBounds == NULL){
                printf("File %s is not in the correct format. Incorrect upperbound found at line %d.\n"
                       ,fileName, lineIndex + 2); return NULL;
            }
            lines++;
            args->setUpperBound = TRUE;
        }else if(readU == 0 && readL == 0){
            points[pointIndex] = readPoint(inputFile,*d);
            if(points[pointIndex] == NULL){
                printf("File %s is not in the correct format. Incorrect point found at line %d.\n"
                       ,fileName, lineIndex + 2); return NULL;
            }
            pointIndex++;
        }else{
            printf("File %s is not in the correct format. Double declaration of bounds found at line %d.\n"
                   ,fileName, lineIndex + 2); return NULL;
        }

        fscanf(inputFile, "\n");
    }

    if (args->setUpperBound == FALSE) free(args->upperBounds);
    if (args->setLowerBound == FALSE) free(args->lowerBounds);

    printf("n=%d d=%d m=%d input_verbose=%d output_verbose=%d sort=%d entropy=%d read_upperbound=%d read_lowerbound=%d\n"
           ,*n, *d, *m, args->inputMode == VERBOSE, args->outputMode == VERBOSE
           ,args->sortedMode == SORTED, args->entropyMode == TRUE
           ,args->setUpperBound==TRUE, args->setLowerBound==TRUE);
    if(args->setUpperBound == TRUE){
        printf("U ");
        printPoint(args->upperBounds, *d);
        printf("\n");
    }
    if(args->setLowerBound == TRUE){
        printf("L ");
        printPoint(args->lowerBounds, *d);
        printf("\n");
    }

    if(args->inputMode != VERBOSE) return points;
    printPoints(points, *n, *d, '\n');
    return points;
}