// Copyright 2019 Niharika Tomar
////////////////////////////////////////////////////////////////////////////////
// Main File:        across.c
// This File:        across.c
// Other Files:      my-look.c, my-diff.c
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
 * across.c finds words of a specified length that contain a specified substring
 * at a specified position
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// driver for the code
int main(int argc, char *argv[]) {
    // Check if number of command-line arguments is correct.
    if (argc != 5 && argc != 4) {
    printf("across: invalid number of arguments\n");
    exit(1);
    }
    // Open the file and check if it opened successfully
    FILE *fp;  // file pointer
    // open file provided by user
    if (argc == 5) {
    fp = fopen((argv[4]), "r");
    } else if (argc == 4) {  // open default file
      fp = fopen("/usr/share/dict/words", "r");
      }
    // check if file opened successfully
    if (fp == NULL) {
    printf("across: cannot open file\n");
    exit(1);
    }
    // check invalid positions :
    // If substring's required starting position extend
    // past the length of the allowed matching words
    if (atoi(argv[3]) <= atoi(argv[2]) + strlen(argv[1]) - 1) {
    printf("across: invalid position\n");
    exit(1);
    }
    // If the length of the substring extend past the
    // length of the allowed matching words
    if (atoi(argv[3]) <= atoi(argv[2])) {
    printf("across: invalid position\n");
    exit(1);
    }

    // variable declarations
    char * buffer;  // stores file's contents
    buffer = malloc(sizeof(char) * 1000);
    size_t size = 1000;  // size for getline
    char *sub = malloc(sizeof(char) * 1000);
    strcpy(sub, argv[1]);  // stores substring
    char *start = malloc(sizeof(char) * 1000);
    char *length = malloc(sizeof(char) * 1000);
    strcpy(start, argv[2]);  // given substring start
    strcpy(length, argv[3]);  // given length of word
    int lowercheck;  // checks if substring is lowercase
    // Reading the file into buffer
    while (getline(&buffer, &size, fp) != -1) {
    // finding words of given length
    if (strlen(buffer) == (atoi(length)+1)) {
    // checking if word from file is lowercase/ignoring special chars
    lowercheck = 0;
    for (int i = 0; i < strlen(buffer) - 1; i++) {
    // if word is not lowercase ret 1
    if (!islower(buffer[i])) {
    lowercheck = 1;
    }
    }
    // if lowercase words found, find substring
    if (lowercheck != 1) {
    // checks if word has the substring
    if (strncmp(buffer+ atoi(start), sub, strlen(sub))== 0) {
    printf("%s", buffer);
    }
    }
    }
    }

    // freeeing memory
    free(buffer);
    buffer = NULL;
    free(sub);
    sub = NULL;
    free(start);
    start = NULL;
    free(length);
    length = NULL;

    // Closing file
    if (fclose(fp) != 0) {
    printf("Error while closing the file\n");  // printing error message
    exit(1);
    }
    return 0;
}


