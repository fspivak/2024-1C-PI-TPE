/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Header para el manejo del front-end del Query 3
** Query 3: Patente con más multas por infracción
*/

#ifndef dictADT_h
#define dictADT_h

#include <stdlib.h>
#include <strings.h>
#include "infractionsADT.h"

typedef struct dictCDT * dictADT;

typedef struct{
    elemType elem;
    elemType cat;
    size_t count; // Cantidad de veces que aparece la misma categoria
} tQueryDict3;

/* Retorna un nuevo dict de elementos. Si dim > 0 entonces copia los elementos del
** vector elem y los inicializa en cero.
*/
dictADT newDict(elemType elems[], size_t dim, status * flag);

/* Retorna el size del bag */
size_t sizeDict(const dictADT dict);

/* Retorna el indice de elem, y -1 si no lo encuentra */
int findDict(const dictADT dict, elemType rec);

/* Inserta un elemento. Si ya existia aumenta su contador sino,
** lo inserta al final y setea su contador en 1
*/
status addDict(dictADT dict, size_t idx, elemType plate);

tQueryDict3 getElemMostPopularDict(dictADT dict, size_t idx);

/* Libera toda la memoria reservada por el TAD */
void freeDict(dictADT dict);

#endif // dictADT_h
