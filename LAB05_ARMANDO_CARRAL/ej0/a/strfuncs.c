#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

/* calcula la longitud de la cadena apuntada por str. */
size_t string_length(const char *str){
   size_t size = 0;
   char *s = (char *)str;
   if(s != NULL){
      for (int i = 0; s[i] != '\0'; ++i) {
         ++size;
      }
   }
   return size;
}

/* Devuelve una nueva cadena en memoria dinámica que se obtiene tomando
   los caracteres de str que son distintos del caracter c. 
*/
char *string_filter(const char *str, char c){
   size_t length = 0;
   char *s = (char *)str;
   for (int i = 0; s[i] != '\0'; ++i) {
      if (s[i] != c) {
         length++;
      }
   }
   //printf("tamaño de la cadena sin '.' es: %ld\n", length);
   //printf("%s\n", s);
   char *array_str = (char *)malloc(length * sizeof(char));
   int j = 0;
   for (int i = 0; s[i] != '\0'; ++i) {
      if (s[i] != c) {
         array_str[j] = s[i];
         j++;
       }
   }

   return array_str;
}
