/*
** Autor: Federico Spivak
** Fecha de Creacion: 05/07/2024
** Archivo para el manejo del back-end del Query 2 y 3
** Query 2: Infracción más popular por agencia emisora
** Query 3: Patente con más multas por infracción 
*/

#ifndef bookADT_h
#define bookADT_h

typedef struct bookCDT * bookADT;

typedef char * elemType;   // cambiar al tipo deseado para que sea mas adaptable

/* Defino funcion que compara elemType (adaptable)
** Retorna:
** - Negativo si e1 es "menor" que e2 (e1 debe estar antes que e2)
** - Cero si son "iguales" (representan lo mismo)
** - Positivo si e1 es "mayor" que e2 (e1 debe estar después que e2)
*/
typedef int (*compare) (const elemType e1, const elemType e2);

/* Estructura para el uso del Query2 y Query3*/
typedef struct queryBook{
    elemType group;
    elemType cat;
    size_t count; // Cantidad de veces que aparece el mismo cat
} tQueryBook;

/* Crea un nuevo TAD vacio con la funcion para comparar elemType*/
bookADT newBook(compare cmp);

/* Almacena un nuevo grupo y su categoria. Si el grupo existe, agrega solo la categoria.
** Si la categoria ya existe, aumenta su contador.
** La variable de entrada grupFormat y catFormat es para saber de que forma almacenar los datos, siendo:
** 0 para que apunte a una direccion
** 1 para almacenar una copia con strcpy
*/
void addBook(bookADT book, elemType group, int grupFormat, elemType cat, int catFormat);

/* Permite iterar por todos los grupos
** Devolviendo la categoria mas popular de cada grupo
** El orden es alfabetico por nombre del grupo.
*/
void toBeginMostPopular(bookADT book);

int hasNextMostPopular(bookADT book);

tQueryBook nextMostPopular(bookADT book);

/* Retorna la categoria que aparece más veces en un grupo. Si hay más de uno 
** con esa condición, usa la funcion compare para elemType.
*/

tQueryBook mostPopularByGroup(bookADT book, elemType group);

void freeBook(bookADT book);

#endif // bookADT_h
