#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x >= 0) {
        *y = x;
    }
    else{
        *y = (-1)*x;
    }
}

int main(void) {

    int res = 0;
    int a = -98;

    absolute(a, &res);  
    /* 
        Aqui absolute(..., &res) estamos enviando la direccion de memoria de res;
        En void absolute(..., int *y) es usada para ingresar al contenido y cambiarlo pero, haciendo la declarion de "int *" 
    */
    printf("res: %d\n", res);
    res = 0;

    return EXIT_SUCCESS;
}

