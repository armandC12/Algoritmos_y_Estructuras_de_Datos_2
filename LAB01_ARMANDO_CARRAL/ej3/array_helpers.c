#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    FILE * open_file;
    open_file = fopen(filepath, "r");
    int cheack_input = fscanf(open_file, "%u", &max_size);
    assert(!(cheack_input == 0));

    unsigned int i = 0;
    while(i < max_size && 0 != max_size){
        fscanf(open_file, "%d", &array[i]);
        i+=1;
    }
    int close_file = fclose(open_file);
    assert(!(close_file != 0));

    return max_size;
}

void array_dump(int a[], unsigned int length) {
    if (length !=0) {
        printf("[");
        for (unsigned int i = 0U; i < length-1; ++i) {
            printf("%d,", a[i]);
        }
        printf("%d]\n", a[length-1]);
    }
    else{
        printf("[ ]\n");
    }

}