#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

int main(void) {
    char user_input[MAX_LENGTH];
    char user_modif [MAX_LENGTH];
    printf("Ingrese su nombre y apellido: ");
    char *res = fgets(user_input, MAX_LENGTH, stdin);
    if(res == NULL){
        fprintf(stderr, "Invalid string.\n");
        exit(EXIT_FAILURE);
    }
    //scanf("%s", user_input);
    //printf("tamaño de la cadena ingresada %ld\n", strlen(user_input));
    memmove(user_modif,user_input,strlen(user_input)-1);
    //printf("tamaño de la cadena modificada %ld\n", strlen(user));

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_modif);

    return EXIT_SUCCESS;
}
