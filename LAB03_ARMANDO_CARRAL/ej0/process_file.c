#include <stdio.h>
#include <stdlib.h>

#include "process_file.h"

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {
    FILE *file;
    file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int size = 0u;
    while(!feof(file) && size < max_size){
    	int res = 0;
    	res = fscanf(file, " %u ", &indexes[size]);
    	if (res != 1) {
    		fprintf(stderr, "Invalid array.\n");
        	exit(EXIT_FAILURE);
        }
        res = 0; 
        res = fscanf(file, "'%c'\n", &letters[size]);
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        //printf(" %d %c\n", indexes[size], letters[size]);
        ++size;
    }
    //printf("%u\n", size);
    fclose(file);

    return size;
}

void array_sorted(char sorted[], unsigned int indexes[], char letters[], unsigned int length){

    for (unsigned int i = 0; i < length; ++i)
    {
        for (unsigned int j = 0; j < length; ++j)
        {
            if(i == indexes[j]){
                sorted[indexes[j]] = letters[j];
            }
        }
    }
}

