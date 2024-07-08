/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Header para el manejo de funciones genericas dentro de mi progrma
*/

#ifndef funGen_h
#define funGen_h
#include <stdio.h>

/* 
** Funcion de comparacion de strings (no es case sensitive)
** Retorna:
** - Negativo si s1 es "menor" que s2 (s1 debe estar antes que s2)
** - Cero si son "iguales" (representan lo mismo)
** - Positivo si s1 es "mayor" que s2 (s1 debe estar después que s2)
*/
int my_strcasecmp(const char *s1, const char *s2);

#endif // funGen_h