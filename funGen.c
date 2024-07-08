/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo de funciones genericas dentro de mi progrma
*/

#include <stdio.h>
#include <ctype.h> 

int my_strcasecmp(const char *s1, const char *s2){
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
