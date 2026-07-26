#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct line {
    char *pLine;
    struct line *pNext;

} LINE;

LINE *readLines(char *pFileName, LINE *pFirst);
void writeLines(char *pFileName, LINE *pFirst);
LINE *addLine(LINE *pFirst, char *pText);
LINE *freeLines(LINE *pFirst);

int main(int argc, char *argv[]) {
    char *pInputName = NULL;
    char *pOutputName = NULL;
    LINE *pFirst = NULL;

    // Too many arguements
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if (argc >= 2) {
        pInputName = argv[1];
    }

    if (argc == 3) {
        pOutputName = argv[2];

        // Check that input and output files are different
        if(strcmp(pInputName, pOutputName) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }

    }
    pFirst = readLines(pInputName, pFirst);
    writeLines(pOutputName, pFirst);
    pFirst = freeLines(pFirst);

    return 0;
}

// Default to reading from stdin
LINE *readLines(char *pFileName, LINE *pFirst) {
    FILE *pFile = stdin;
    char *pLine = NULL;
    size_t iSize = 0;

    // Read from file when input filename is given
    if(pFileName != NULL) {
        if ((pFile = fopen(pFileName,"r")) == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", pFileName);
            exit(1);
        }
    }

    while(getline(&pLine, &iSize, pFile) != -1) {
        pFirst = addLine(pFirst, pLine);
        pLine = NULL;
        iSize = 0;
    }

    free(pLine);
    pLine = NULL;

    if(pFile != stdin) {
        fclose(pFile);
    }

    return(pFirst);
}

// Default to writing to stdout
void writeLines(char *pFileName, LINE *pFirst) {
    FILE *pFile = stdout;
    LINE *ptr = pFirst;

    // Write to file when output filename is given
    if (pFileName != NULL) {
        if ((pFile = fopen(pFileName, "w")) == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", pFileName);
            exit(1);
        }
    }

    while (ptr != NULL) {
        fprintf(pFile, "%s", ptr->pLine);
        ptr = ptr->pNext;
    }

    if (pFile != stdin) {
        fclose(pFile);
    }

    return;
}

// Allocate memory for a new line and set it to the beginning of the list 
LINE *addLine(LINE *pFirst, char *pLine) {
    LINE *pNew = NULL;
    
    if ((pNew = (LINE *)malloc(sizeof(LINE))) == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    pNew->pLine = pLine;
    pNew->pNext = pFirst;

    return(pNew);
    
}

LINE *freeLines(LINE *pFirst) {
    LINE *ptr = pFirst;

    while (ptr != NULL) {
        pFirst = ptr->pNext;

        free(ptr->pLine);
        ptr->pLine = NULL;
        
        free(ptr);
        ptr = pFirst;
    }

    return(pFirst);
}