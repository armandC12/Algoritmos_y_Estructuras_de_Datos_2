/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int option (void){
    int opcion;
    /* Mostrar el menu */
    printf("1: Mostrar árbol por pantalla\n");
    printf("2: Agregar un elemento\n");
    printf("3: Eliminar un elemento\n");
    printf("4: Chequear existencia de elemento\n");
    printf("5: Mostrar la longitud del árbol\n");
    printf("6: Mostrar raíz, maximo y mínimo del árbol\n");
    printf("7: Salir\n\n");
        //printf("8: Ver el menu otra vez")
        /* Solicitamos que ingrese la opción. */
    printf("Seleccione una opción: ");
    int res = fscanf(stdin,"%d", &opcion);
    if(res != 1){
        fprintf(stderr, "Not read data.\n");
        exit(EXIT_FAILURE);
    }
    return opcion;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /* Se sale del ciclo si option es igual a 's' */
    int res;
    int ver;
    int opcion;
    abb_elem e;

    do{
        printf("Si desea ver el menu de opciones ingrese el 0, de lo contrario, ingrese el 7: ");
        res = fscanf(stdin,"%d", &ver);
        if(res != 1){
            fprintf(stderr, "Not read data.\n");
            exit(EXIT_FAILURE);
        }
        printf("\n");
        if(ver == 0){
            opcion = option();
        } else {
            opcion = ver;
        }

        switch(opcion){
            case 1:
                printf("\nEl arbol es:\n");
                abb_dump(tree);
                printf("\n\n");
            break;

            case 2:
                printf("Ingrese el elemento: ");
                res = fscanf(stdin,"%d", &e);
                if(res != 1) {
                    fprintf(stderr, "Not read data.\n");
                    exit(EXIT_FAILURE);
                }
                tree = abb_add(tree,e);
                printf("\n\n");
            break;

            case 3:
                printf("Ingrese el elemento a eliminar: ");
                res = fscanf(stdin,"%d", &e);
                if(res != 1) {
                    fprintf(stderr, "Not read data.\n");
                    exit(EXIT_FAILURE);
                }
                while(!abb_exists(tree, e)){
                    printf("El elemento no se encuentra en el arbol, ingrese otra vez: ");
                    res = fscanf(stdin,"%d", &e);
                    if(res != 1) {
                        fprintf(stderr, "Not read data.\n");
                        exit(EXIT_FAILURE);
                    }
                }
                tree = abb_remove(tree,e);
                printf("\n\n");
            break;

            case 4:
                printf("\nIngrese el elemento: ");
                res = fscanf(stdin,"%d", &e);
                if(res != 1) {
                    fprintf(stderr, "Not read data.\n");
                    exit(EXIT_FAILURE);
                }
                if(abb_exists(tree,e)) {
                    printf("el elemento ingresado si existe en el arbol.\n\n");
                } else {
                    printf("El elemento ingresado no existe en el arbol.\n\n");
                }
            break;

            case 5:
                printf("\nLa longitud del arbol es: %d\n\n", abb_length(tree));
            break;

            case 6:
                if (!abb_is_empty(tree)) {
                    printf("\n ");
                    printf("raiz: %d\n minimo: %d\n maximo: %d\n\n", abb_root(tree),
                                                                   abb_min(tree),
                                                                   abb_max(tree));
                } else {
                    printf("\nÁrbol vacío\n");
                }
            break;

            case 7:
                tree = abb_destroy(tree);
                printf("Exiting.\n");
                return (EXIT_SUCCESS);
            break;
            default:
                printf("\n\"%d\" is invalid. Please choose a valid "
                       "option.\n\n", opcion);
        }

    } while(opcion != 7);

    return (EXIT_SUCCESS);
}

    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */

    /*
    abb_elem eliminanodo;
    printf("Ingrese el nodo a eliminar\n");
    fscanf(stdin, "%d", &eliminanodo);
    tree = abb_remove(tree,eliminanodo);
    abb_dump(tree);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
        printf(" tamaño: %d\n", abb_length(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }
    */