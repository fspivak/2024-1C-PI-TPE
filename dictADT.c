/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo del front-end del Query 3
** Query 3: Patente con más multas por infracción
*/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include "dictADT.h"
#include "infractionsADT.h"

#define BLOCK 10

typedef struct {
    char plate[PLATE];
    int count;
} tPlate;

typedef struct{
    elemType elem;
    tPlate * plates;
    int plateDim;
    int plateSize;
} tRecord;

struct dictCDT{
    tRecord * elems;
    size_t size;
};

dictADT newDict(elemType elems[], size_t dim, status * flag){
    errno = 0;
    dictADT new = malloc(sizeof(struct dictCDT));
    if(new == NULL || errno == ENOMEM){
        *flag = NO_MEMORY;
        return NULL; // ante un error retorna NULL, sin hacer cambios 
    }
    new->size = dim;

    if ( dim > 0 ) {
        tRecord * aux = calloc(1, dim * sizeof(aux[0]));
        if(aux == NULL || errno == ENOMEM){
            *flag = NO_MEMORY;
            return NULL; // ante un error retorna NULL, sin hacer cambios
        }
        new->elems = aux;
	    for(size_t i = 0; i < dim; i++){
		    new->elems[i].elem = elems[i];
        }
	} else {
	    new->elems = NULL;
	}
	return new;
}

size_t sizeDict(const dictADT d){
    return d->size;
}

int findDict(const dictADT d, elemType elem){
    for (int i = 0; i < sizeDict(d) ; i++){
        if(compare(d->elems[i].elem, elem) == 0){
            return i;
        }
    }
    return -1;
}

static status addPlate(tRecord * r, elemType plate){
    for (size_t i = 0; i < r->plateDim ; i++){
        if(compare(r->plates[i].plate, plate) == 0){
            r->plates[i].count++;
        }
    }
    if(r->plateDim == r->plateSize){
        r->plateSize += BLOCK;
        errno = 0;
        tPlate * aux = realloc(r->plates, r->plateSize*sizeof(r->plates[0]));
        if(aux == NULL || errno == ENOMEM){
            return NO_MEMORY;
        }
        r->plates = aux;
    }
    strcpy(r->plates[r->plateDim].plate, plate);
    r->plates[r->plateDim].count = 1;
    r->plateDim++;
    return OK;
}

status addDict(dictADT d, size_t idx, elemType plate){
    return addPlate(&d->elems[idx], plate);
}

tQueryDict3 getElemMostPopularDict(dictADT d, size_t idx){
    tQueryDict3 ans = {
        .elem = NULL,
        .cat = NULL,
        .count = 0
    };

    if(d->elems[idx].plateDim > 0){
        ans.elem = d->elems[idx].elem;
        tRecord aux = d->elems[idx]; // nodo auxiliar de categoria
        ans.cat = aux.plates[0].plate; // Categoria con mayor repeticion dentro del grupo
        ans.count = aux.plates[0].count; // Mayor valor de categoria repetida del grupo
        for (size_t i = 1; i < aux.plateDim; i++){
            if(aux.plates[i].count > ans.count || (aux.plates[i].count==ans.count && (compare(aux.plates[i].plate, ans.cat)<0))){
                ans.cat = aux.plates[i].plate;
                ans.count = aux.plates[i].count;
            }
        }
    }

    return ans;
}

void freeDict(dictADT d){
    for (size_t i = 0; i < d->size; i++){
        if(d->elems[i].plateDim > 0){
            free(d->elems[i].plates);
        }
    }
    free(d->elems);
    free(d);
    return;
}
