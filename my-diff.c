// Copyright 2019 Niharika Tomar
////////////////////////////////////////////////////////////////////////////////
// Main File:        my-diff.c
// This File:        my-diff.c
// Other Files:      my-look.c, across.c
// Semester:         CS 537 FALL 2019
//
// Author:           Niharika Tomar
// Email:            ntomar@wisc.edu
// CS Login:         tomar
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

/*
my-diff.c takes two files as input and then outputs the lines that are different
across the two of them. my-diff will compare line i from file A and line i from
file B; if the two lines are identical, my-diff prints nothing; if the two lines
are different, my-diff prints out the line number followed by the line i from 
file A and from file B
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function declaration to compare 2 files
void compare(FILE * fp1, FILE * fp2);

// driver for the code
int main(int argc, char *argv[]) {
    // Open the file and read
    FILE *fp1;  // file pointer initialisations
    FILE *fp2;
    // argumnet check
    if (argc == 3) {
    fp1 = fopen((argv[1]), "r");  // file reading
    fp2 = fopen((argv[2]), "r");
    } else {
      printf("my-diff: invalid number of arguments\n");
      exit(1);
      }
    // check if files opened successfully
    if (fp1 == NULL || fp2 == NULL) {
    printf("my-diff: cannot open file\n");  // printing error message
    exit(1);
    }
    /* Call function to compare file */
    compare(fp1, fp2);

    // Closing file and checking if it closed
    if (fclose(fp1) != 0) {
    printf("Error while closing the file\n");  // printing error message
    exit(1);
    }
    if (fclose(fp2) != 0) {
    printf("Error while closing the file\n");  // printing error message
    exit(1);
    }
    return 0;
}

/**
 * Function to compare files.
 * Returns nothing if both files are same, else returns
 * line number where both file differ along with the differing contents.
 */
void compare(FILE * fp1, FILE * fp2) {
    // memory allocation for contents of file 1
    char * bufferA;
    bufferA = malloc(sizeof(char) * 1000);
    size_t sizeA = 0;
    // memory allocation for contents of file 2
    char * bufferB;
    bufferB = malloc(sizeof(char) * 1000);
    size_t sizeB = 0;
    int line = 1;  // tracker for line number in file
    int odd = 0;  // tracker for finding consecutive line differnce
    int fileA = getline(&bufferA, &sizeA, fp1);  // holds file1 result
    int fileB = getline(&bufferB, &sizeB, fp2);  // holds  file1 2 result

    // checking till EOF reached
    while (fileA != -1 && fileB != -1) {
    // getting rid of trailing newline
    // for file 1
    if (bufferA[strlen(bufferA)-1] == '\n') {
    bufferA[strlen(bufferA)-1] = '\0';
    }
    // for file 2
    if (bufferB[strlen(bufferB)-1] == '\n') {
    bufferB[strlen(bufferB)-1] = '\0';
    }
    // checking for substrings
    if (strcmp(bufferA, bufferB) != 0) {
    if (odd < 1) {  // if consecutive lines are different
    printf("%d\n", line);  // printing line number
    }
    printf("< %s\n", bufferA);  // printing file 1 content
    printf("> %s\n", bufferB);  // printing file 2 content
    odd++;  // incrementing counter for consec. lines
    } else {
    odd = 0;  // resetting counter
    }
    // vars to read and save file content
    fileA = getline(&bufferA, &sizeA, fp1);
    fileB = getline(&bufferB, &sizeB, fp2);
    line++;  // incremneting line number
    }
    // if file 1 hasn't reached the end but file 2 has
    if (fileA != -1) {
    if (odd < 1) {  // if consecutive lines are different
    printf("%d\n", line);  // printing line number
    }
    // checking till EOF reached
    while (fileA != -1) {
    // getting rid of trailing newline
    if (bufferA[strlen(bufferA)-1] == '\n') {
    bufferA[strlen(bufferA)-1] = '\0';
    }
    // printing remaining lines from file 1
    printf("< %s\n", bufferA);
    // getting next word from file
    fileA = getline(&bufferA, &sizeA, fp1);
    }
    }
    // if file 2 hasn't reached the end but file 1 has
    if (fileB != -1) {
    // if consecutive lines are different
    if (odd < 1) {
    // printing line number
    printf("%d\n", line);
    }
    // checking till EOF reached
    while (fileB != -1) {
    // getting rid of trailing newline
    if (bufferB[strlen(bufferB)-1] == '\n') {
    bufferB[strlen(bufferB)-1] = '\0';
    }
    // printing remaining lines from file 2
    printf("> %s\n", bufferB);
    // getting next word from file
    fileB = getline(&bufferB, &sizeB, fp2);
    }
    }
    // freeeing memory
    free(bufferA);
    bufferA = NULL;
    free(bufferB);
    bufferB = NULL;
    }

