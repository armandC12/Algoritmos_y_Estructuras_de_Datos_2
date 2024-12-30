#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define MAX_CAPACITY 100

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

/* En los casos que corresponda se debe definir una función booleana invrep() 
   que verifique que la instancia que se le pasa como parámetro cumpla
   las propiedades de la invariante. 
*/
static bool invrep(stack s) {
    return (s != NULL || 0 <= ((int)s->size));
}

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->capacity = MAX_CAPACITY;
    s->elems = (stack_elem *)calloc(s->capacity, sizeof(int));
    s->size = 0;
    assert(invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    if(s->size == s->capacity){
        size_t size = s->capacity * sizeof(int);
        s->elems = (stack_elem *)realloc(s->elems,size);
        s->elems[s->size] = e;
        s->size = s->size + 1;
    } else {
        s->elems[s->size] = e;
        s->size = s->size + 1;
    }
    assert(invrep(s));

    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    s->size = s->size - 1u;
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s){
    unsigned lenght = 0;
    if (s != NULL) {
        lenght = s->size;
    }
    assert(invrep(s));
    return lenght;
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s){
    bool empty = s == NULL;
    if(s != NULL){
        empty = s->size == 0u;
    }
    return empty;
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    stack_elem *array = NULL;
    if (s != NULL) { 
        unsigned int i = 0u;
        array = (int *)calloc((size_t)s->size, sizeof(int));
        while(i < s->size){
            array[i] = s->elems[i];
            ++i;
        }
    }
    assert(invrep(s));
    return array;
}

stack stack_destroy(stack s){
    assert(invrep(s));
    free(s->elems);
    s->elems = NULL;
    s->size = 0u;
    s->capacity = MAX_CAPACITY;
    free(s);
    s = NULL;

    return s;
}