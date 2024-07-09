#include "infractionsADT.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct infractionsCDT{
    elemType *v;
    size_t dim;  // Cantidad de espacios ocupados
    size_t size; // Tamaño del vector
};

static char * copyStr(const char *word) {
    errno = 0;
    char *ans = malloc((strlen(word) + 1) * sizeof(char));
    if (ans == NULL || errno == ENOMEM) {
        return NULL;
    }
    return strcpy(ans, word);
}

int compare(const void *a, const void *b) {
    return strcasecmp((const char *)a, (const char *)b);
}

/* Inicializa la estructura de infracciones */
infractionsADT newInfractions(status * flag){
    infractionsADT new = calloc(1, sizeof(struct infractionsCDT));
    if (new == NULL || errno == ENOMEM) {
        *flag = NO_MEMORY;
        return NULL;
    }
    return new;
}

/* Lee las infracciones desde un archivo CSV */
status readInfractions(FILE *file, infractionsADT infractions) {
    char line[LINE];
    char *token;
    tRecordInfraction record;

    fgets(line, LINE, file); // Lee la primera línea (encabezado)
    while (fgets(line, LINE, file) != NULL) {
        token = strtok(line, DELIMITER);
        record.id = atoi(token);

        token = strtok(NULL, END_LINE);
        strcpy(record.description, token);

        if (infractions->size <= record.id) {
            elemType *aux = realloc(infractions->v, (record.id + 1) * sizeof(elemType));
            if (aux == NULL || errno == ENOMEM) {
                return NO_MEMORY;
            }
            infractions->v = aux;
            for (size_t i = infractions->size; i <= record.id; i++) {
                infractions->v[i] = NULL;
            }
            infractions->size = record.id + 1;
        }

        infractions->v[record.id] = copyStr(record.description);
        if (infractions->v[record.id] == NULL) {
            return NO_MEMORY;
        }
        infractions->dim++;
    }
    return OK;
}

/* Retorna  1 si pertence a las infracciones, y 0 si no lo encuentra */
int belongsInfractions(infractionsADT infractions, size_t idx){
    return idx<infractions->size && infractions->v[idx]!=NULL;
}

elemType * getInfractions(infractionsADT infractions){
    return infractions->v;
}

elemType findInfraction(const infractionsADT infractions, size_t idx){
    return infractions->v[idx];
}

size_t sizeInfractions(infractionsADT infractions){
    return infractions->size;
}


/* Libera la memoria utilizada por la estructura de infracciones */
void freeInfractions(infractionsADT infractions) {
    for (size_t i = 0; i < infractions->size; i++) {
        if (infractions->v[i] != NULL) {
            free(infractions->v[i]);
        }
    }
    free(infractions->v);
    free(infractions);
}
