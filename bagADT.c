/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo del back-end del Query 1
** Query 1: Total de multas por infraccion
** Manejo de un bag de elementos genericos en forma de vector para luego
** ordenarlo por cantidad de apariciones de cada elemento
*/

#include <stdio.h>
#include <errno.h>
#include "bagADT.h"

typedef struct element{
    elemType elem;
    size_t count; // Cantidad de veces que aparece el mismo elemento
} tElement;

struct bagCDT{
    tElement * v;
    size_t size; // Cantidad de elementos insertados (sin repetir)
};

bagADT newBag(void){
    errno = 0;
    bagADT new = calloc(1, sizeof(struct bagCDT));
    if(new == NULL || errno == ENOMEM){
        return NULL; // ante un error retorna NULL, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
    }
    return new;
}

size_t sizeBag(const bagADT bag){
    return bag->size;
}

int findBag(const bagADT bag, elemType elem){
    for (int i = 0; i < sizeBag(bag) ; i++){
        if(compare(bag->v[i].elem, elem) == 0){
            return i;
        }
    }
    return -1;
}

void addBag(bagADT bag, elemType elem){
    int idx = findBag(bag, elem);
    if(idx >= 0){
        bag->v[idx].count++;
        return;
    }
    // si idx es < 0 es porque no existe en el bag
    errno = 0;
    tElement * aux = realloc(bag->v, (bag->size + 1) * sizeof(tElement));
    if (aux == NULL || errno == ENOMEM){
        return; // ante un error retorna el mismo vector, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
    }
    bag->v = aux;
    bag->v[bag->size].elem = elem;
    bag->v[bag->size].count = 1;
    bag->size++;
    return;
}

/* Funcino Auxiliar para ordenar de manera descendente el bag */
static int cmpCount(const tElement * e1, const tElement * e2){
    if(e1->count < e2->count){
        return 1;
    }
    else if(e1->count > e2->count){
        return -1;
    }
    else{ //e1->count == e2->count
        return compare(e1->elem, e2->elem);
    }
}

void sortBag(bagADT bag){
    qsort(bag->v, bag->size, sizeof(tElement), ((int (*)(const void *, const void *)) cmpCount));
    return;
}

elemType getBag(bagADT bag, size_t idx, int * count){
    *count = bag->v[idx].count; 
    return bag->v[idx].elem;
}

void freeBag(bagADT bag){
    free(bag->v);
    free(bag);
    return;
}