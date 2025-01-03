#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = izq;
    unsigned int i = izq + 1u;
    unsigned int j = der;
    while(i <= j) {
        if (goes_before(a[i], a[ppiv])) { 
            i += 1u;
        }
        else if (goes_before(a[ppiv], a[j])) {
            j -= 1u;
        }
        else if (goes_before(a[ppiv], a[i]) && goes_before(a[j], a[ppiv])) {
            swap(a, i, j);
            i += 1u;
            j -= 1u;
        }
    }
    swap(a, ppiv, j);
    ppiv = j;
    
    return ppiv;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    if (izq < der) {
        unsigned int ppiv = partition(a, izq, der);
        assert(izq <= ppiv && ppiv <= der);   /*Invariante*/
        if (izq < ppiv){
            quick_sort_rec(a, izq, ppiv - 1u);
        }
        if (ppiv < der) {
            quick_sort_rec(a, ppiv + 1u, der);
        }
    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

