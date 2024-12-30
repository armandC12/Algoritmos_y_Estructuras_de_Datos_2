#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
	stack_elem elem;	//Campo para el elemento 
	stack next;			//Puntero al siguiente nodo
};

/* No pedimos memoria porque no hace falta guardar un elemento */
stack stack_empty() {
	return NULL;
}

stack stack_push(stack s, stack_elem e){
	stack s2 = malloc(sizeof(struct _s_stack));
	s2->elem = e;
	s2->next = s;
	s = s2;
	return s;
}

stack stack_pop(stack s){
	assert(s != NULL);    //invariante
	stack p = s;
	s = s->next;
	p->next = NULL;
	free(p);

	return s;
}

unsigned int stack_size(stack s){
	unsigned int n = 0;
	if(s != NULL){
		stack p = s;
		n = 1;
		while(p->next != NULL){
			n += 1;
			p = p->next;
		}
	}
	return n;
}

stack_elem stack_top(stack s){
	assert(s != NULL); //invariante
	return s->elem;
}

bool stack_is_empty(stack s){
	return s == NULL;
}

/*El elemento superior de la pila se convierte 
  en el elemento situado más a la derecha de la matriz.*/
stack_elem *stack_to_array(stack s){
	stack_elem *array = NULL;
	if (s != NULL) {
		unsigned int length = stack_size(s); 
		unsigned int i = length - 1;
		stack p = s;
		array = (int*)calloc((size_t)length, sizeof(int));
		while(p->next != NULL){
			array[i] = p->elem;
			p = p->next;
			--i;
		}
		array[i] = p->elem;
	}
	return array;
}

stack stack_destroy(stack s){
	if(s != NULL){
		stack p = s;
		while(p != NULL){
			s = p;
			p = p->next;
			free(s);
		}
		s = NULL;
	}
	return s;
}
