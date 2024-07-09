/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo del back-end del Query 2
** Query 2: Infracción más popular por agencia emisora
*/

#ifndef bookADT_h
#define bookADT_h

#include "infractionsADT.h"

typedef struct bookCDT * bookADT;

/* Estructura para el uso del Query2 y Query3*/
typedef struct{
    elemType group;
    elemType cat;
    size_t count; // Cantidad de veces que aparece el mismo cat
} tQueryBook2;

/* Crea un nuevo TAD vacio*/
bookADT newBook(status * flag);

/* Almacena un nuevo grupo y su categoria. Si el grupo existe, agrega solo la categoria.
** Si la categoria ya existe, aumenta su contador.
*/
status addBook(bookADT book, elemType group, elemType cat);

/* Permite iterar por todos los grupos
** Devolviendo la categoria mas popular de cada grupo
** El orden es alfabetico por nombre del grupo.
*/
void toBeginMostPopular(bookADT book);

int hasNextMostPopular(bookADT book);

tQueryBook2 nextMostPopular(bookADT book);

void freeBook(bookADT book);

#endif // bookADT_h
