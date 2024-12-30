#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

#define MAX_SIZE 5

int main(void) {

//	stack_elem array[MAX_SIZE];
	stack s = stack_empty();

/*	printf("Ingrese los valores\n");
	for (unsigned int i = 0u ; i < MAX_SIZE; ++i) {
		scanf("%d", &array[i]);
		s = stack_push(s, array[i]);
	}
*/
	printf("tamaño de la pila: %d\n", stack_size(s));

	stack_elem *a = stack_to_array(s);

	unsigned int n = stack_size(s);
	for (unsigned int i = 0; i < n; ++i) {
		printf("%d ", stack_top(s));
		s = stack_pop(s);
	}
	printf("\n");

	for (unsigned int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");

	s = stack_destroy(s);
	
//	s = stack_push(s, 2);

	if(stack_is_empty(s)){
		printf("pila vacía\n");
	} else {
		printf("pila no vacía\n");
	}

	return EXIT_SUCCESS;
}
/*
	s = stack_push(s, array[0]);
	//printf("tamaño de la pila: %d\n", stack_size(s));
	s = stack_push(s, array[1]);
	printf("tamaño de la pila: %d\n", stack_size(s));
	
	stack_elem e = stack_top(s);
	printf("elemento tope: %d\n", e);

	printf("aplicamos la funcion stack_pop\n");
	s = stack_pop(s);
	printf("tamaño de la pila: %d\n", stack_size(s));
	
	e = stack_top(s);
	printf("elemento tope: %d\n", e);
*/
