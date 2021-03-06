/*
 * Grant Toepfer - TCSS 333 - HW3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 16
#define MAX_NUM_NAMES 1000
#define MAX_NUM_YEARS 11
#define FILENAME_LEN 18
#define MAX_LINE_LEN 26

void initializeArrays(char** names, int** ranks) {
    int i, j;
    for (i = 0; i < MAX_NUM_NAMES; i++) {
        names[i] = NULL;
        ranks[i] = (int*) malloc(sizeof(int) * MAX_NUM_YEARS);
        for (j = 0; j < MAX_NUM_YEARS; j++) {
            ranks[i][j] = -1;
        }
    }
 
}

int getIndex(char** names, char* name) {
    int i;
    for (i = 0; i < MAX_NUM_NAMES; i++) {
        if(NULL == names[i]) {
            names[i] = name;
            return i;
        } else if (0 == strcmp(names[i], name)) {
            free(name);
            return i;
        }
    }
    return -1;
}

void parseLine(char** names, int** ranks, int yearIndex, char* line) {
    char* name;
    name = (char*) malloc(sizeof(char) * MAX_NAME_LEN);
    int num;
    sscanf(line, "%[^,],F,%d", name, &num);
    
    int index = getIndex(names, name);

    ranks[index][yearIndex] = num;
}

void readInputFile(char** names, int** ranks, int yearIndex) {
    char file[FILENAME_LEN];
    int year = 1910 + 10 * yearIndex;
    sprintf(file, "names/yob%d.txt", year);
    
    FILE* in = fopen(file, "r");

    if(NULL == in) {
        printf("%s failed to open!", file);
        exit(2);
    }

    char* line = (char*) malloc(sizeof(char) * MAX_LINE_LEN);
    int i;
    for (i = 0; i < 100; i++) {
        fgets(line, MAX_LINE_LEN, in);
        parseLine(names, ranks, yearIndex, line);
    }
    free(line);
    fclose(in);
}

void readInputFiles(char** names, int** ranks) {
    int i;
    for (i = 0; i < MAX_NUM_YEARS; i++) {
        readInputFile(names, ranks, i);
    }
}


void swap(char** names, int** ranks, int indexTo, int indexFrom) {
    int* tempInts = ranks[indexTo];
    char* tempChars = names[indexTo];

    ranks[indexTo] = ranks[indexFrom];
    names[indexTo] = names[indexFrom];

    ranks[indexFrom] = tempInts;
    names[indexFrom] = tempChars;
}

void sortArrays(char** names, int** ranks) {
    int i, j;
    for (i = 0; NULL != names[i]; i++) {
        for (j = i; 0 < j && 0 > strcmp(names[j], names[j - 1]); j--) {
            swap(names, ranks, j, j - 1);
        }
    }
}

void outputToFile(char** names, int** ranks) {
    FILE* out = fopen("summary.csv", "w");
    int i, j;
    fprintf(out, "Name");
    for(i = 0; i < 11; i++) {
        fprintf(out, ",%d", 1910 + 10 * i);
    }
    fprintf(out, "\n");

    for (i = 0; NULL != names[i]; i++) {
        fprintf(out, "%s", names[i]);
        for (j = 0; j < MAX_NUM_YEARS; j++) {
            if(-1 == ranks[i][j]) fprintf(out, ",");
            else fprintf(out, ",%d", ranks[i][j]);
        }
        fprintf(out, "\n");
    }

    fclose(out);
}

void destroy(char** names, int** ranks) {
    int i, j;

    for (i = 0; i < MAX_NUM_NAMES; i++) {
        if(NULL != names[i]) free(names[i]);
    }

    for (i = 0; i < MAX_NUM_NAMES; i++) {
        free(ranks[i]);
    }
}

int main(void) {
    char** names = (char**) malloc(sizeof(char*) * MAX_NUM_NAMES);
    int** ranks = (int**) malloc(sizeof(int*) * MAX_NUM_NAMES);

    initializeArrays(names, ranks);
    readInputFiles(names, ranks);
    sortArrays(names, ranks);
    outputToFile(names, ranks);
    destroy(names, ranks); 
   
    free(names);
    free(ranks);
    return 0;
}
