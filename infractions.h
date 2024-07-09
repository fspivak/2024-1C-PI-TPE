#ifndef INFRACTIONS_H
#define INFRACTIONS_H

#include <stddef.h>

typedef struct {
    size_t id;
    char description[51];
} tInfractions;

enum status {OK=0, FILE_NOT_FOUND, NO_MEMORY};

/* Lee las infracciones desde un archivo y almacena en un array dinámico */
int readInfractions(FILE *file, tInfractions **records, size_t *count);

/* Escribe las infracciones en el archivo query1.csv */
void writeQuery1(FILE *file, tInfractions *records, size_t count);

#endif // INFRACTIONS_H
