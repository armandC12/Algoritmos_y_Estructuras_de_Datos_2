#include <stdlib.h>
#include <assert.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t dict) {
    bool d = false;
    if (dict == NULL){
        d = true;
    } else {
        if (dict->left == NULL && dict->right == NULL){
            d = true;
        } else {
            if (dict->left != NULL){
                /* tree->elem > tree->left->elem */
                if (key_less(dict->left->key, dict->key)){
                    d = invrep(dict->left);
                }
            }
            if (dict->right != NULL){
                /* tree->elem < tree->right->elem */
                if (key_less(dict->key, dict->right->key)) {
                    d = invrep(dict->right);
                }
            }
        }
    }
    return d;
}

static key_t dict_max_key (dict_t dict);

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    /* PRE: {dict --> dict_t /\ word --> key_t /\ def --> value_t} */
    assert(invrep(dict));
    if(dict == NULL){
        dict = malloc(sizeof(struct _node_t));
        dict->left = NULL;
        dict->right = NULL;
        dict->key = word;
        dict->value = def;
    } else if(key_eq(dict->key, word)){
        dict->value = value_destroy(dict->value);
        dict->value = def;
    } else {
        if(key_less(word, dict->key)){
            dict->left = dict_add(dict->left, word, def);
        } else  if (key_less(dict->key, word)) {
            dict->right = dict_add(dict->right, word, def);
        }
    }
    /* POS: {dict --> dict_t /\ key_eq(def, dict_search(dict, word))} */
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def;
    /* PRE: {dict --> dict_t /\ word --> key_t}*/
    assert(invrep(dict));
    if(dict == NULL){
        def = NULL;
    } else if(key_eq(dict->key, word)){
        def = dict->value;
    } else {
        if(key_less(word, dict->key)){
            def = dict_search(dict->left, word);
        } else if (key_less(dict->key, word)) {
            def = dict_search(dict->right, word);
        }
    }
    /* POS: {(def != NULL) == dict_exists(dict, word)} */
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exists;
    /* PRE: {dict --> dict_t /\ word --> key_t} */
    assert(invrep(dict));
    if(dict == NULL){
        exists = false;
    } else if (key_eq(dict->key, word)) {
        exists = true;
    } else {
        if(key_less(word, dict->key)){
            exists = dict_exists(dict->left, word);
        } else if (key_less(dict->key, word)) {
            exists = dict_exists(dict->right, word);
        }
    }
    /* POS: {dict --> dict_t} */
    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    assert(invrep(dict));
    if(dict != NULL){
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if(dict != NULL){
        /* Caso posibles de eliminar: hoja, nodo con un hijo y nodo con dos hijos */
        if (key_eq(dict->key, word) ){
            /* analizo los casos a eliminar */
            /* Hoja */
            if(dict->left == NULL && dict->right == NULL){       //funciona bien
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = NULL;
            }
            /* Nodo con un hijo */
            else if(dict->left != NULL && dict->right == NULL){  //funciona bien
                dict_t dict_aux = dict->left;
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = dict_aux;
            }
            else if(dict->left == NULL && dict->right != NULL){  //funciona bien
                dict_t dict_aux = dict->right;
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = dict_aux;
            }
            /* Nodo con dos hijos */
            else {
                /* Tenemos que buscar el maximo de lado izquierdo y reemplazarlo por la raiz */
                key_t aux_key = dict_max_key(dict->left);
                value_t aux_value = dict_search(dict->left, aux_key);
                /* se lo asignamos a la raiz del nodo actual y luego lo eliminamos */
                dict = dict_remove(dict, aux_key);
                //dict->key = key_destroy(dict->key);
                //dict->value = value_destroy(dict->value);
                dict->key = aux_key;
                dict->value = aux_value;
            }
        } else {
            if (key_less(word, dict->key)) {
                dict->left = dict_remove(dict->left, word);
            }
            else if (key_less(dict->key, word)) {
                dict->right = dict_remove(dict->right, word);
            }
        }
    }

    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));

    if(dict != NULL){
        if(dict->left == NULL && dict->right == NULL){
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            dict = NULL;
        } else {
            dict->left = dict_remove_all(dict->left);
            dict->right = dict_remove_all(dict->right);
            dict = dict_remove_all(dict);
        }
    }

    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL) {
        dict_dump(dict->left, file);
        fprintf(file, "%s : %s\n", string_ref(dict->key), string_ref(dict->value));
        dict_dump(dict->right, file);

    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));

    if(dict != NULL){
        if(dict->left == NULL && dict->right == NULL){
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            dict = NULL;
        } else {
            dict->left = dict_destroy(dict->left);
            dict->right = dict_destroy(dict->right);
            dict = dict_destroy(dict);
        }
    }
    free(dict);
    dict = NULL;

    assert(dict == NULL);  //si o si tree tiene que apuntar a NULL, caso contrario salta un advertencia.

    return dict;
}

/* FUNCION AUXILIAR */
static key_t dict_max_key (dict_t dict) {
    key_t max_key;
    assert(invrep(dict));

    max_key = dict->key;
    if (dict->right != NULL) {
        if (key_less(max_key, dict->right->key)) {
            max_key = dict_max_key(dict->right);
        }
    }
    else if(dict->left != NULL) {
        if (key_less(max_key, dict->left->key)) {
            max_key = dict_max_key(dict->left);
        }
    }

    assert(invrep(dict) && dict_exists(dict, max_key));
    return max_key;
}

/*
void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL) {
        //printf("%s : %s\n\n", key_dump(dict->key, stdout), value_dump(dict->value, stdout));
        //printf("%s : %s\n\n", string_ref(dict->key), string_ref(dict->value));
        fprintf(file, "%s : %s\n", string_ref(dict->key), string_ref(dict->value));
        dict_dump(dict->right, file);
        dict_dump(dict->left, file);

    }
}
*/