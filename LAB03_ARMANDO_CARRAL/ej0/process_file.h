#ifndef _PROCCES_FILE_H
#define _PROCCES_FILE_H

/* Extraigo los datos del archivo */
unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size);

/* ordenamos el arreglo sorted para la impresion */
void array_sorted(char sorted[], unsigned int indexes[], char letters[], unsigned int length);

#endif //_PROCCES_FILE_H
