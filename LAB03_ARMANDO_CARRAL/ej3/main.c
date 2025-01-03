/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int *pointer_one = NULL;
    char *pointer_two = NULL;

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};

    pointer_one = &x;
    *pointer_one = *(&(m.age))/10;

    pointer_one = &m.age;
    int value = *pointer_one;         //guardo el valor(90) apuntado por pointer_one antes de ser modificado, porque luego lo usaremos.
    *pointer_one = *pointer_one + 10;

    pointer_two = &m.name_initial;
    *pointer_two = 'F';

    pointer_one = &a[1];
    *pointer_one = value/2 - *(&a[3]);

    /* Completar aquí:
       Al finalizar la ejecución las variables deben tener los siguientes valores
       x = 9
       m = (100, F)
       a[1] = 42

       Las restricciones son:
       - No usar las variables 'x', 'm' y 'a' en la parte izquierda de alguna asignación.
       - Se pueden agregar líneas de código, pero no modificar las que ya existen.
       - Se pueden declarar hasta 2 punteros.
       AYUDA: podes usar GDB para consultares valores de variables y la dirección de memoria donde estan alojadas.
    */

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);
}
