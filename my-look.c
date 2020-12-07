// Copyright 2019 Niharika Tomar
////////////////////////////////////////////////////////////////////////////////
// Main File:        my-look.c
// This File:        my-look.c
// Other Files:      across.c, my-diff.c
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
 * my-look is a simple program based on the utility look. It take a string as 
 * input and return any lines in a file that contain that string as an input;
 * if a file isn't specified, the file /usr/share/dict/words is used by default
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// driver for program
int main(int argc, char *argv[]) {
    // Check if number of command-line arguments is correct.
    if (argc == 1 || argc > 3) {
    printf("my-look: invalid number of arguments\n");
    exit(1);
    }
    // Open the file and check if it opened successfully
    FILE *fp;  // file pointer
    // open file provided by user
    if (argc == 3) {
    fp = fopen(argv[2], "r");
    } else if (argc == 2) {   // open default file
      fp = fopen("/usr/share/dict/words", "r");
      }
    // check if file opened successfully
    if (fp == NULL) {
    printf("my-look: cannot open file\n");
    exit(1);
    }

    // variable declarations
    char * buffer;  // stores file's contents
    buffer = malloc(sizeof(char) * 1000);
    size_t size = 1000;  // size for getline
    char *sub = malloc(sizeof(char) * 1000);
    strcpy(sub, argv[1]);  // stores substring

    // Reading the file into buffer
    while (getline(&buffer, &size, fp) != -1) {
    // checking for substring with case insensitive comparison
    int i = strncasecmp(buffer, sub, strlen(sub));
    if (i == 0) {  // if substring found
    printf("%s", buffer);  // printing file contents
    }
    }

    // freeeing memory
    free(buffer);
    buffer = NULL;
    free(sub);
    sub = NULL;

    // Closing file
    if (fclose(fp) != 0) {
    printf("Error while closing the file\n");  // printing error message
    exit(1);
    }
  return 0;
}

