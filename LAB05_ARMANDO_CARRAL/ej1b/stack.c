#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
	stack_elem elem;
	stack next;
	unsigned int size;
};

static bool invrep(stack s) {
	bool s_check = true;
	if(s != NULL) {
		s_check = s->size > 0u; 
	}
	return s_check;
}


stack stack_empty() {
	return NULL;
}

stack stack_push(stack s, stack_elem e){
	if(s == NULL){
		stack s2 = malloc(sizeof(struct _s_stack));
		s2->elem = e;
		s2->next = NULL;
		s2->size = 1;
		s = s2;
	}
	else if(s != NULL) {
		stack s2 = malloc(sizeof(struct _s_stack));
		s2->elem = e;
		s2->size = s->size + 1;
		s2->next = s;
		s = s2;
	}
	assert(invrep(s)); //Aqui va la invariante: s != NULL && s->size > 0
	return s;
}

stack stack_pop(stack s){
	assert(s != NULL && invrep(s));    //invariante
	stack p = s;
	s->size = s->size - 1;
	s = s->next;
	free(p);
	return s;
}

unsigned int stack_size(stack s){
	assert(invrep(s));
	unsigned int size = 0u;
	if(s != NULL){
		size = s->size;
	}
	return size;
}

stack_elem stack_top(stack s){
	assert(s != NULL && invrep(s)); //invariante
	return s->elem;
}

bool stack_is_empty(stack s){
	return s == NULL;
}

stack_elem *stack_to_array(stack s){
	assert(invrep(s));
	stack_elem *array = NULL;
	if (s != NULL) {
		unsigned int length = stack_size(s); 
		unsigned int i = length - 1;
		stack p = s;
		array = (int*)calloc((size_t)length, sizeof(int));
		while(p->next != NULL){
			array[i] = p->elem;
			--i;
			p = p->next;
		}
		array[i] = p->elem;
	}
	assert(invrep(s));
	return array;
}

stack stack_destroy(stack s){
	assert(invrep(s));
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
