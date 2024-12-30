#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

/* Si ninguna de esos dos condiciones se cumple entonces no es un Arbol Binario de Busqueda */
/* (1)chequea que los valores alojados en el subarbol izquierdo sean menores que la raiz */
/* (2)chequea que los valores alojados en el subarbol derecho sean mayores que la raiz */
static bool invrep(abb tree) {
    bool b = false;
    if (tree == NULL){
        b = true;
    } else {
        if (tree->left == NULL && tree->right == NULL){
            b = true;
        } else {
            if (tree->left != NULL){
                /* tree->elem > tree->left->elem */
                if (tree->elem > tree->left->elem){
                    b = invrep(tree->left);
                }
            }
            if (tree->right != NULL){
                /* tree->elem < tree->right->elem */
                if (tree->elem < tree->right->elem) {
                    b = invrep(tree->right);
                }
            }
        }
    }
    return b;
}

abb abb_empty(void) {
    abb tree = NULL; 
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL){
            tree = malloc(sizeof(struct _s_abb));
            tree->elem = e;
            tree->left = NULL;
            tree->right = NULL;
    } else {
        /* Verifica si tree->elem > e */
        if (elem_less(e, tree->elem)){
            tree->left = abb_add(tree->left, e);
        }
        /* Verifica si tree->elem < e */
        else if (elem_less(tree->elem, e)){
            tree->right = abb_add(tree->right,e);
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty = false;  //Suponemos que no esta vacío tree
    assert(invrep(tree));
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists =  false;   //Suponemos que no existe, caso contrario devuelve true
    assert(invrep(tree));
    if (tree != NULL) {
        if (elem_eq(tree->elem, e)) {
            exists = true;
        } else {
            if (elem_less(e, tree->elem)){
                exists = abb_exists(tree->left, e);
            }
            else if (elem_less(tree->elem, e)){
                exists = abb_exists(tree->right, e);
            }
        }
    }

    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length = 0;
    assert(invrep(tree));
    if (tree != NULL){
        length = 1 + 
                 abb_length(tree->left) + 
                 abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    
    /* Caso posibles de eliminar: hoja, nodo con un hijo y nodo con dos hijos */
    if (tree->elem == e ){
        /* analizo los casos a eliminar */
        /* Hoja */
        if(tree->left == NULL && tree->right == NULL){
            free(tree);
            tree = NULL;
        }
        /* Nodo con un hijo */
        else if(tree->left != NULL && tree->right == NULL){
            abb tree_aux = tree->left;
            free(tree);
            tree = tree_aux;
        }
        else if(tree->left == NULL && tree->right != NULL){
            abb tree_aux = tree->right;
            free(tree);
            tree = tree_aux;
        } else { /* Nodo con dos hijos */
            /* Tenemos que buscar el maximo de lado izquierdo y reemplazarlo por la raiz */
            abb_elem aux_elem = abb_max(tree->left);
            /* se lo asignamos a la raiz del nodo actual y luego lo eliminamos */
            tree = abb_remove(tree,aux_elem);
            tree->elem = aux_elem;
        }
    } else {
        if (tree->elem > e) {
            tree->left = abb_remove(tree->left,e);
        }
        else if (tree->elem < e) {
            tree->right = abb_remove(tree->right,e);
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    max_e = tree->elem;
    if (tree->right != NULL){
        if (elem_less(max_e, tree->right->elem)){
            max_e = abb_max(tree->right);
        }
    }
    else if(tree->left != NULL){
        if (elem_less(max_e, tree->left->elem)){
            max_e = abb_max(tree->left);
        }
    }

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    min_e = tree->elem;
    if (tree->left != NULL){
        if (elem_less(tree->left->elem, min_e)){
            min_e = abb_min(tree->left);
        }
    }
    else if (tree->right != NULL){
        if (elem_less(tree->right->elem, min_e)){
            min_e = abb_min(tree->right);
        }
    }

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

    if (tree->left != NULL) {
        tree->left = abb_destroy(tree->left);
    }
    if (tree->right != NULL) {
        tree->right = abb_destroy(tree->right);
    }
    free(tree);
    tree = NULL;

    assert(tree == NULL);//si o si tree tiene que apuntar a NULL, caso contrario salta un advertencia.
    return tree;
}

/* abb_dump que muestra el archivo original
void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}
*/

/* Destroy que no funciona:
    if (tree != NULL){
        if(tree->left == NULL && tree->right == NULL){
            free(tree);
            tree = NULL;
        } else {
            if(tree->left != NULL){
                tree = abb_destroy(tree->left);
            }
            else if (tree->right != NULL) {
                tree = abb_destroy(tree->right);
            }
        }
    }
*/