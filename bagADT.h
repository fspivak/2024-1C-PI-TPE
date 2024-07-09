/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Header para el manejo del front-end del Query 1
** Query 1: Total de multas por infraccion
** Manejo de un bag de elementos genericos en forma de vector para luego
** ordenarlo por cantidad de apariciones de cada elemento
*/

#ifndef bagADT_h
#define bagADT_h

#include "infractionsADT.h"
#include <stdlib.h>
#include <strings.h>

typedef struct bagCDT * bagADT;

/* Estructura para el uso del Query1*/
typedef struct{
    elemType elem;
    size_t count; // Cantidad de veces que aparece el mismo elemento
} tQueryBag1;

/* Retorna un nuevo bag de elementos genéricos. Al inicio está vacío */
bagADT newBag(status * flag);

/* Retorna la cantidad de elementos distintos que hay en el bag */
size_t sizeBag(const bagADT bag);

/* Retorna el indice de elem, y -1 si no lo encuentra */
int findBag(const bagADT bag, elemType elem);

/* Inserta un elemento. Si ya existia aumenta su contador sino,
** lo inserta al final y setea su contador en 1
*/
status addBag(bagADT bag, elemType elem);

/* Ordena el bag de elementos de forma descendente por su cantidad.
** En caso de empate en cantidad, ordena por la funcion compare
*/
void sortBag(bagADT bag);

/* Retorna el elemento y cantidad del indice idx.*/
tQueryBag1 getElemBag(bagADT bag, size_t idx);

/* Libera toda la memoria reservada por el TAD */
void freeBag(bagADT bag);

#endif // bagADT_h
