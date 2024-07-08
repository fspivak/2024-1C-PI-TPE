/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo del back-end del Query 2 y 3
** Query 2: Infracción más popular por agencia emisora
** Query 3: Patente con más multas por infracción 
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "bookADT.h"

// Nodo de Categoria
struct nodeC{
    elemType elem;
    int elemFormat; // Formato de almacenamiento del elem
    size_t count; // Cantidad de veces que se repitio esa Categoria
    struct nodeC * tailC;
};

typedef struct nodeC * tNodeC;

// Nodo de Grupo
struct nodeG{
    elemType elem; 
    int elemFormat; // Formato de almacenamiento del elem
    struct nodeG * nextG; // Next Grupo
    tNodeC firstC; // First Categoria
};

typedef struct nodeG * tNodeG;

struct bookCDT{
    tNodeG firstG; // First Grupo
    tNodeG iterG; // Iter Grupo
    size_t size; // Cantidad total de grupos
    compare cmp; // Funcion de comparacion
};

bookADT newBook(compare cmp){
    errno = 0;
    bookADT new = calloc(1, sizeof(struct bookCDT)); //firstG=NULL, iterG=NULL, iterC==NULL, size=0
    if(new == NULL || errno == ENOMEM){
        return NULL; // ante un error retorna NULL, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
    }
    new->cmp = cmp;
    return new;
}

static char * copyStr(elemType elem){
    elemType ans = malloc((strlen(elem)+1) * sizeof(elem[0]));
    if (ans == NULL || errno == ENOMEM){
        return NULL; // ante un error retorna NULL, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
    }
    return strcpy(ans, elem);
}

static tNodeC addContact(tNodeC l, elemType cat, int catFormat, compare cmp){
    int c;
    
    // l==NULL o l->elem > cat -> la categoria no existe -> lo creo
    if(l == NULL || (c=cmp(l->elem, cat)) > 0){
        // Valido espacio en memoria
        errno = 0;
        tNodeC new = malloc(sizeof(struct nodeC));
        if(new == NULL || errno == ENOMEM){
            return l; // ante un error retorna el nodo de categoria, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
        }
        // Forma de almacenar elem
        new->elem = (catFormat == 0) ? cat : copyStr(cat);
        new->elemFormat = catFormat;
        new->count = 1;
        new->tailC = l;
        return new;
    }
    // l->elem < cat -> puede estar mas adelante
    else if(c < 0){
        l->tailC = addContact(l->tailC, cat, catFormat, cmp);
    }
    else{// l->elem == cat -> ya existe la categoria
        l->count++;
    }
    
    return l; // este return sirve para c==0 y c<0
}

static tNodeG addGroup(tNodeG g, elemType group, int grupFormat, elemType cat, int catFormat, compare cmp, int * flag){
    int c;

    // g==NULL o g->elem > group -> el grupo no existe -> lo creo
    if(g == NULL || (c=cmp(g->elem, group)) > 0){
        // Valido espacio en memoria
        errno = 0;
        tNodeG new = malloc(sizeof(struct nodeG));
        if(new == NULL || errno == ENOMEM){
            return g; // ante un error retorna el nodo de grupo, sin hacer cambios -> checkeo en main si errno es distinto de cero y voy al front para explicar porque se detuvo la ejecucion
        }
        // Forma de almacenar elem
        new->elem = (grupFormat == 0) ? group : copyStr(group);
        new->elemFormat = grupFormat;
        new->nextG = g;
        *flag = 1;
        new->firstC = NULL;
        new->firstC = addContact(new->firstC, cat, catFormat, cmp);
        return new;
    }
    // g->elem < group -> puede estar mas adelante
    else if(c < 0){
        g->nextG = addGroup(g->nextG, group, grupFormat, cat, catFormat, cmp, flag);
    }
    else{// g->name == group -> ya existe el grupo
        g->firstC = addContact(g->firstC, cat, catFormat, cmp);
    }
    
    return g; // este return sirve para c==0 y c<0
}

void addBook(bookADT b, elemType group, int grupFormat, elemType cat, int catFormat){
    int flag = 0;
    b->firstG = addGroup(b->firstG, group, grupFormat, cat, catFormat, b->cmp, &flag);
    b->size += flag; // Aumento si es que agrego un nuevo grupo
}

void toBeginMostPopular(bookADT b){
    b->iterG = b->firstG;
}

int hasNextMostPopular(bookADT b){
    return b->iterG != NULL;
}

tQueryBook nextMostPopular(bookADT b){
    tQueryBook ans;
    ans.group = b->iterG->elem;

    tNodeC aux = b->iterG->firstC; // nodo auxiliar de categoria
    ans.cat = aux->elem; // Categoria con mayor repeticion dentro del grupo
    ans.count = aux->count; // Mayor valor de categoria repetida del grupo
    aux = aux->tailC;

    while (aux != NULL){
        // en el caso de empate de count, me quedo con el de menor orden alfabético
        if(aux->count > ans.count || (aux->count==ans.count && (b->cmp(aux->elem, ans.cat)<0))){
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
    if(c->elemFormat){ // elemFormat es 1 -> libero el espacio almacenado
        free(c->elem);
    }
    free(c);
    return;
}

static void freeBookGroup(tNodeG g){
    if(g == NULL){
        return;
    }
    freeBookGroup(g->nextG);
    freeBookCat(g->firstC);
    if(g->elemFormat){ // elemFormat es 1 -> libero el espacio almacenado
        free(g->elem);
    }
    free(g);
    return;

}

void freeBook(bookADT b){
    freeBookGroup(b->firstG);
    free(b);
    return;
}
