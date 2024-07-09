#ifndef INFRACTIONS_ADT_H
#define INFRACTIONS_ADT_H

#include <stdio.h>
#include <strings.h>
#include <stddef.h>

#define LINE 200
#define INFRACTION 51
#define PLATE 11
#define AGENCY 36
#define DELIMITER ";"
#define END_LINE "\n"

typedef enum {OK=0, NO_MEMORY, FILE_NOT_FOUND } status;
typedef char * elemType; // cambiar al tipo deseado para que sea mas adaptable

/* Defino funcion que compara elemTypeBag (adaptable)
** Retorna:
** - Negativo si e1 es "menor" que e2 (e1 debe estar antes que e2)
** - Cero si son "iguales" (representan lo mismo)
** - Positivo si e1 es "mayor" que e2 (e1 debe estar después que e2)
*/
int compare(const void *a, const void *b);

typedef struct{
    size_t id;
    char description[INFRACTION];
} tRecordInfraction;

typedef struct{
    char plate[PLATE];
    size_t infractionId;
    char issuingAgency[AGENCY];
} tRecordTicketNYC;

typedef struct{
    char plateRedacted[PLATE];
    char unitDescription[AGENCY];
    size_t infractionCode;
} tRecordTicketCHI;

typedef struct infractionsCDT *infractionsADT;

/* Inicializa la estructura de infracciones */
infractionsADT newInfractions(status * flag);

/* Lee las infracciones desde un archivo CSV y las almacena */
status readInfractions(FILE *file, infractionsADT infractions);

/* Retorna  1 si pertence a las infracciones, y 0 si no lo encuentra */
int belongsInfractions(infractionsADT infractions, size_t idx);

/* Retorna un puntero a donde se almacenan las infractions */
elemType * getInfractions(infractionsADT infractions);

/* Retorna el elemento del indice idx */
elemType findInfraction(const infractionsADT infractions, size_t idx);

/* Retorna la cantidad de infracciones */
size_t sizeInfractions(infractionsADT infractions);

/* Libera la memoria utilizada por la estructura de infracciones */
void freeInfractions(infractionsADT infractions);

#endif // INFRACTIONS_ADT_H
