/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool ret = x->rank <= y->rank;
    return ret;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

static void swap(player_t atp[], unsigned int i, unsigned int j) {
    struct _player_t temp;
    temp = *atp[i];
    *atp[i] = *atp[j];
    *atp[j] = temp;

}

static unsigned int partition(player_t atp[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = izq;
    unsigned int i = izq + 1u;
    unsigned int j = der;
    while(i <= j) {
        if (goes_before(atp[i], atp[ppiv])) { 
            i += 1u;
        }
        else if (goes_before(atp[ppiv], atp[j])) {
            j -= 1u;
        }
        else if (goes_before(atp[ppiv], atp[i]) && goes_before(atp[j], atp[ppiv])) {
            swap(atp, i, j);
            i += 1u;
            j -= 1u;
        }
    }
    swap(atp, ppiv, j);
    ppiv = j;
    
    return ppiv;
}

static void quick_sort_rec(player_t atp[], unsigned int izq, unsigned int der) {
    if (izq < der) {
        unsigned int ppiv = partition(atp, izq, der);
        assert(izq <= ppiv && ppiv <= der);   //Invariante
        if (izq < ppiv){
            quick_sort_rec(atp, izq, ppiv - 1u);
        }
        if (ppiv < der) {
            quick_sort_rec(atp, ppiv + 1u, der);
        }
    }
}

void sort(player_t atp[], unsigned int length) {
    quick_sort_rec(atp, 0u, (length == 0u) ? 0u : length - 1u);
}

//cpu time used to sort the array: 0.003593 seconds.