#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0) {
        y = x;
    }
    else{
        y = (-1)*x;
    }
}

int main(void) {

    int res = 0;
    int a = -98;

    absolute(a, res);

    printf("res: %d\n", res);
    res = 0;

    /* EL VALOR QUE SE MUESTRA POR PANTALLA NO COINCIDE CON EL VALOR DEL LENGUAJE DEL TEORICO */
    return EXIT_SUCCESS;
}

