/**
*  @file strfuncs.h
*  @brief string functions definition
*/
#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__

#include <stdlib.h>

/* calcula la longitud de la cadena apuntada por str. */
size_t string_length(const char *str);

/* Devuelve una nueva cadena en memoria dinámica que se obtiene tomando
   los caracteres de str que son distintos del caracter c. 
*/
char *string_filter(const char *str, char c);

#endif
