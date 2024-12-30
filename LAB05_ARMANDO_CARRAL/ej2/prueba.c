#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

#define MAX_SIZE 1

int main(void) {

	printf("Creamos un pila\n");
	stack s = stack_empty();
	printf("tamaño de la pila: %d\n", stack_size(s));

	printf("agregamos un elemento a la pila\n");
	s = stack_push(s,7);
	s = stack_push(s,5);
	s = stack_push(s,10);
	s = stack_push(s,55);

	printf("elemento tope de la pila: %d\n", stack_top(s));
	printf("tamaño de la pila: %d\n", stack_size(s));

	unsigned int n = stack_size(s);
	stack_elem *a = stack_to_array(s);
	for (unsigned int i = 0; i < n ; ++i) {
		printf(" %d ", a[i]);
	}
	printf("\n");

/*	printf("eliminamos el elemento tope de la pila\n");
	s = stack_pop(s);
	printf("tamaño de la pila: %d\n", stack_size(s));

 	s = stack_destroy(s);
*/
	if(stack_is_empty(s)){
		printf("pila vacía\n");
	} else {
		printf("pila no vacía\n");
	}

	return EXIT_SUCCESS;
}
