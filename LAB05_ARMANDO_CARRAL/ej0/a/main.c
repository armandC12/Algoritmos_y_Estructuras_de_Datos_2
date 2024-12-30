#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"


int main(void) {
    char *some_str="h.o.l.a m.u.n.d.o.!";
    char *filtered=NULL;

    filtered = string_filter(some_str, '.');
    printf("original: '%s' (%ld)\n"
           "filtrada: '%s' (%ld)\n",
           some_str, string_length(some_str),
           filtered, string_length(filtered));

    free(filtered);
    filtered = NULL;

    return EXIT_SUCCESS;
}

/* Cada arreglo de tipo char(cadena) en c debe terminar  con el caracter '\0'
   Ejemplo: char cadena [5];
   Tiene capacidad para guardar un string de hasta 4 caracteres de lonigutd,
   por lo cual ya tenemos un lugar ocupado. Entonces se puede almacenar en cadena
   una palabra con longitud de entre uno y cuatro caracteres, pero inlcuso también
   se puede guardar una plabra vacía(en ese caso cadena[0] = '\0').
   Para armar un string podemos hacer:
        char cadena[5]={'h', 'o', 'l', 'a', '\0'};
        printf("cadena: %s\n", cadena);

   Otra forma más comoda:
        char cadena[5]="hola";
        printf("cadena: %s\n", cadena);
   En este caso el caracter '\0' se implicitamente en el arreglo cadena

   Para no tener que contar la cantidad de caracteres que necesitamos se puede definir
   una cadena directamente haciendo:
        char cadena[]="hola mundo!";
        printf("cadena: %s\n", cadena);
   el contenido del array es el siguiente:
        cadena: 'h' 'o' 'l' 'a' ' ' 'm' 'u' 'n' 'd' 'o' '!' '\0'
                 0   1   2   3   4   5   6   7   8   9   10  11
   Como ya se vio, los arreglos y los punteros son cosas muy parecidas en C, 
   por lo que también es valido hacer lo siguiente:
        char *cadena="hola mundo!";
        printf("cadena: %s\n", cadena);
   dsf

 */