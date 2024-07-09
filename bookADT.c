/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo del back-end del Query 2
** Query 2: Infracción más popular por agencia emisora
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "bookADT.h"
#include "infractionsADT.h"

// Nodo de Categoria
struct nodeC{
    elemType elem;
    size_t count; // Cantidad de veces que se repitio esa Categoria
    struct nodeC * tailC;
};

typedef struct nodeC * tNodeC;

// Nodo de Grupo
struct nodeG{
    elemType elem; 
    struct nodeG * nextG; // Next Grupo
    tNodeC firstC; // First Categoria
};

typedef struct nodeG * tNodeG;

struct bookCDT{
    tNodeG firstG; // First Grupo
    tNodeG iterG; // Iter Grupo
    size_t size; // Cantidad total de grupos
};

bookADT newBook(status * flag){
    errno = 0;
    bookADT new = calloc(1, sizeof(struct bookCDT)); //firstG=NULL, iterG=NULL, iterC==NULL, size=0
    if(new == NULL || errno == ENOMEM){
        *flag = NO_MEMORY;
        return NULL; // ante un error retorna NULL, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
    }
    return new;
}

static char * copyStr(elemType elem){
    elemType ans = malloc((strlen(elem)+1) * sizeof(elem[0]));
    if (ans == NULL || errno == ENOMEM){
        return NULL; // ante un error retorna NULL, sin hacer cambios
    }
    return strcpy(ans, elem);
}

static tNodeC addCategory(tNodeC l, elemType cat, status * flag){
    int c;
    
    // l==NULL o l->elem > cat -> la categoria no existe -> lo creo
    if(l == NULL || (c=compare(l->elem, cat)) > 0){
        // Valido espacio en memoria
        errno = 0;
        tNodeC new = malloc(sizeof(struct nodeC));
        if(new == NULL || errno == ENOMEM){
            *flag = NO_MEMORY;
            return l; // ante un error retorna el nodo de categoria, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
        }
        // Forma de almacenar elem
        new->elem = cat;
        new->count = 1;
        new->tailC = l;
        return new;
    }
    // l->elem < cat -> puede estar mas adelante
    else if(c < 0){
        l->tailC = addCategory(l->tailC, cat, flag);
    }
    else{// l->elem == cat -> ya existe la categoria
        l->count++;
    }
    
    return l; // este return sirve para c==0 y c<0
}

static tNodeG addGroup(tNodeG g, elemType group, elemType cat, int * add, status * flag){
    int c;

    // g==NULL o g->elem > group -> el grupo no existe -> lo creo
    if(g == NULL || (c=compare(g->elem, group)) > 0){
        // Valido espacio en memoria
        errno = 0;
        tNodeG new = malloc(sizeof(struct nodeG));
        if(new == NULL || errno == ENOMEM){
            *flag = NO_MEMORY;
            return g; // ante un error retorna el nodo de grupo, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
        }
        // Forma de almacenar elem
        new->elem = copyStr(group);
        new->nextG = g;
        *add = 1;
        new->firstC = NULL;
        new->firstC = addCategory(new->firstC, cat, flag);
        return new;
    }
    // g->elem < group -> puede estar mas adelante
    else if(c < 0){
        g->nextG = addGroup(g->nextG, group, cat, add, flag);
    }
    else{// g->name == group -> ya existe el grupo
        g->firstC = addCategory(g->firstC, cat, flag);
    }
    
    return g; // este return sirve para c==0 y c<0
}

status addBook(bookADT b, elemType group, elemType cat){
    int add = 0;
    status flag = OK;
    b->firstG = addGroup(b->firstG, group, cat, &add, &flag);
    b->size += add; // Aumento si es que agrego un nuevo grupo
    return flag;
}

void toBeginMostPopular(bookADT b){
    b->iterG = b->firstG;
}

int hasNextMostPopular(bookADT b){
    return b->iterG != NULL;
}

tQueryBook2 nextMostPopular(bookADT b){
    tQueryBook2 ans;
    ans.group = b->iterG->elem;

    tNodeC aux = b->iterG->firstC; // nodo auxiliar de categoria
    ans.cat = aux->elem; // Categoria con mayor repeticion dentro del grupo
    ans.count = aux->count; // Mayor valor de categoria repetida del grupo
    aux = aux->tailC;

    while (aux != NULL){
        // en el caso de empate de count, me quedo con el de menor orden alfabético
        if(aux->count > ans.count || (aux->count==ans.count && (compare(aux->elem, ans.cat)<0))){
            ans.cat = aux->elem;
            ans.count = aux->count;
        }
        aux = aux->tailC;
    }
    // Apunto al siguiente grupo
    b->iterG = b->iterG->nextG;
    return ans;
}

static void freeBookCat(tNodeC c){
    if(c == NULL){
        return;
    }
    freeBookCat(c->tailC);
    free(c);
    return;
}

static void freeBookGroup(tNodeG g){
    if(g == NULL){
        return;
    }
    freeBookGroup(g->nextG);
    freeBookCat(g->firstC);
    free(g->elem);
    free(g);
    return;

}

void freeBook(bookADT b){
    freeBookGroup(b->firstG);
    free(b);
    return;
}
