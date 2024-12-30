#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


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
    /* no implementes partition, ya está implementado en sort_helpers.o
       (no se puede leer, pero en sort_helpers.h vas a encontrar información
        para saber cómo usarlo)
    */
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}

/*
printf("pivot: %d\n", ppiv);
      for(unsigned int i=0; i < der; ++i){
         printf("%d ", a[i]);
      }
      printf("\n");
*/