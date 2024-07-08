/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Header para el manejo del front-end del Query 1
** Query 1: Total de multas por infraccion
** Este ranking no guarda en el heap el elemType sino que hace un puntero al lugar de donde le pasaron el elemType
** Como el manejo es interno yo voy a mantener en un vector de elemType general con los datos y lo que hago es apuntar a ellos
** Esto me hace el manejo de datos mas liviano porque estoy haciendo swap de un struct que contiene un puntero y un size_t
*/

#ifndef bagADT_h
#define bagADT_h

#include <stdlib.h>
#include "funGen.h"

typedef struct bagCDT * bagADT;

typedef const char * elemType;   // cambiar al tipo deseado para que sea mas adaptable

/* Defino funcion que compara elemType (adaptable)
** Retorna:
** - Negativo si e1 es "menor" que e2 (e1 debe estar antes que e2)
** - Cero si son "iguales" (representan lo mismo)
** - Positivo si e1 es "mayor" que e2 (e1 debe estar después que e2)
*/
#pragma GCC diagnostic ignored "-Wunused-function"
static int compare(elemType e1, elemType e2) {
	return my_strcasecmp(e1, e2);
}
#pragma GCC diagnostic warning "-Wunused-function"

/* Retorna un nuevo bag de elementos genéricos. Al inicio está vacío */
bagADT newBag(void);

/* Retorna la cantidad de elementos distintos que hay en el bag */
size_t sizeBag(const bagADT bag);

/* Retorna el indice de elem, y -1 si no lo encuentra */
int findBag(const bagADT bag, elemType elem);

/* Inserta un elemento. Si ya existia aumenta su contador sino,
** lo inserta al final y setea su contador en 1
*/
void addBag(bagADT bag, elemType elem);

/* Ordena el bag de elementos de forma descendente por su cantidad.
** En caso de empate en cantidad, ordena por la funcion compare
*/
void sortBag(bagADT bag);

/* 
** Retorna el elemento del indice idx.
** Dejando en count la cantidad de veces repetido,
** siendo 0 en caso de no pertenecer al bag
*/
elemType getBag(bagADT bag, size_t idx, int * count);

/* Libera toda la memoria reservada por el TAD */
void freeBag(bagADT bag);

#endif // bagADT_h