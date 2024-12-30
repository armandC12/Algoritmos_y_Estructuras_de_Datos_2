#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef int list_elem;
typedef struct _node * list;

list empty (void);
/* crea una lista vacía */

list addl (list l, list_elem e);
/* agrega el elemento e al comienzo de la lista l*/

bool is_empty (list l);
/* Devuelve True si l es vacía */

list_elem head (list l);
/* Devuelve el primer elemento de la lista l */
/* PRE: not is_empty(l)*/

list tail (list l);
/* Elimina el primer elemnto de la lista l */
/* PRE: not is_empty(l) */

list addr(list l, list_elem e);
/* agrega el elemnto e al final de la lista l */

unsigned int length (list l);
/* Devuelve la cantidad de elementos de la lista l */

list concat (list l, list l2);
/* Agrega al final de l todos los elementos de l0 en el mismo orden */

list_elem index (list l, unsigned int n);
/* Devuelve el n-esimo elemento de la lista l */
/* PRE: lenght(l) > n */

list take (list l, unsigned int n);
/* Deja en l sólo los primeros n elementos, elimando el resto */

list drop (list l, unsigned int n);
/* Elimina los primeros n elementos de l */

list copy_list (list l1);
/* Copia todos los elementos de l1 en la nueva lista l2*/

list destroy (list l);
/*Libera memoria en caso que sea necesario*/

#endif