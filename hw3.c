/*
 * Grant Toepfer - TCSS 333 - HW3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 16
#define MAX_NUM_NAMES 1000
#define MAX_NUM_YEARS 10

void initializeArrays(char** names, int** ranks) {
    int i;
    names = (char**) malloc(sizeof(char*) * MAX_NUM_NAMES);
    for (i = 0; i < MAX_NUM_NAMES; i++) {
        names[i] = (char*) malloc(sizeof(char) * MAX_NAME_LEN);
    }

    ranks = (int**) malloc(sizeof(int*) * MAX_NUM_NAMES);
    for (i = 0; i < MAX_NUM_NAMES; i++) {
        ranks[i] = (int*) malloc(sizeof(int) * MAX_NUM_YEARS);
    }    
}

void readInputFile(char** names, int** ranks, int yearIndex) {
    
}

void readInputFiles(char** names, int** ranks) {
    int i;
    for (i = 0; i < 10; i++) {
        readInputFile(names, ranks, i);
    }
}

int main(void) {
    char** names;
    int** ranks;

    initializeArrays(names, ranks);
    readInputFiles(names, ranks);
    sortArrays(names, ranks);
    outputArrays(names, ranks);
    
    free(names);
    free(ranks);
    
    return 0;
}
