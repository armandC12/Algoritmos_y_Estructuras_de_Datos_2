#include "mybool.h"

/* Extrae de un archivo la longitud y los elementos de un arreglo
   y devuelve la longitud del arreglo */
unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath);

/* Imprime por pantalla el arreglo */
void array_dump(int a[], unsigned int length);

/* Dado un array a[] y su tamaño length debe devolver true si y sólo si los
   elementos del arreglo a[] están ordenados de manera ascendente,
   Caso contrario devolvera false */
mybool array_is_sorted(int a[], unsigned int length);
