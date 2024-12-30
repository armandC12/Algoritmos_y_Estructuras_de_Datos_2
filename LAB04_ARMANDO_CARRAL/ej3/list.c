#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array_helpers.h"

#include "list.h"

struct _node{
	list_elem elem;
	list next;
};

list empty (void) {
	return NULL;
}

list addl (list l, list_elem e){
	list p = malloc(sizeof(struct _node));
	p->elem = e;
	p->next = l;
	l = p;
	return l;
}

bool is_empty (list l) {
	return l == NULL;
}

list_elem head (list l) {
	assert(!(is_empty(l)));
	return l->elem;
}

list tail (list l) {
	assert(!(is_empty(l)));
	list p = l;
	l = l->next;
	free(p);
	p = NULL;
	return l;
}

list addr(list l, list_elem e) {
	list p = NULL;
	list q = malloc(sizeof(struct _node));
	q->elem = e;
	q->next = NULL;
	if (!(is_empty(l))) {
		p = l;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = q;
	} else {
		l = q;
	}
	return l;
}

unsigned int length (list l) {
	list p = NULL;
	unsigned int n = 0;
	p = l;
	while(p != NULL){
		++n;
		p = p->next;
	}
	return n;
}

list concat (list l1, list l2){
	list p = NULL;
	p = l1;
	while(p->next != NULL){
		p = p->next;
	}
	p->next = l2;

	return l1;
}

list_elem index (list l, unsigned int n){
	assert(length(l) > n);
	list p = NULL;
	unsigned int pos = 0;
	p = l;
	while(p->next != NULL && pos == n){
		p = p->next;
		pos += 1;
	}
	return p->elem;
}

list take (list l, unsigned int n){
	list p = NULL;
	list q = NULL;
	unsigned int pos = 1;
	p = l;
	while(p->next != NULL && pos < n-1) {
		p = p->next;
		pos += 1;
	}
	q = p->next;
	p->next = NULL;
	while(q->next != NULL){
		p = q;
		free(p);
		q = q->next;
	}
	return l;
}

list drop (list l, unsigned int n) {
	list p = NULL;
	unsigned int pos = 1;
	p = l;
	while(l->next != NULL && pos < n){
		l = l->next;
		pos += 1;
		free(p);
		p = l;
	}
	return l;
}

list copy_list (list l1){
	list p = NULL;
	list l2 = empty();
	p = l1;
	while(!(is_empty(p))){
		l2 = addr(l2,p->elem);
		p = p->next;
	}
	return l2;
}

list destroy (list l){
	assert(is_empty(l));
	list p = NULL;
	p = l;
	while(!is_empty(p)) {
		l = p;
		p = p->next;
		free(l);
	}
	l = NULL;
	return l;
}
