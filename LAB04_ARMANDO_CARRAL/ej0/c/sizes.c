#include <stdio.h>
#include <stdlib.h>

#include "data.h"

/* La función malloc() toma un parámetro de tipo size_t (muy parecido a unsigned int) que es la
   cantidad de memoria en bytes que se solicita reservar. */

/* El operador sizeof() devuelve la cantidad de bytes ocupados por una expresión o tipo */

/* Completar el archivo sizes.c para que muestre el tamaño en bytes de cada miembro de la
   estructura data_t por separado y el tamaño total que ocupa la estructura en memoria.
   ¿La suma de los miembros coincide con el total? ¿El tamaño del campo name depende 
   del nombre que contiene?
*/

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Messi", 34, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name),
                                       sizeof(messi.age),
                                       sizeof(messi.height),
                                       sizeof(messi));

    return EXIT_SUCCESS;
}

/* ¿La suma de los miembros coincide con el total? 
   Rta: No coincide, porque el size de data_t es de 40 bytes, y la suma de los miembros es de 38 bytes.

   ¿El tamaño del campo name depende del nombre que contiene?
   Rta: El tamaño del campo name no depende del nombre contenido, 
        porque se reserva con anteriodidad el tamaño para guardar una cadena.
*/