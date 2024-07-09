#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infractions.h"

#define LINE 100
#define BLOCK 10
#define DELIMITER ";"
#define END_LINE "\n"

int readInfractions(FILE *file, tInfractions **records, size_t *count) {
    char line[LINE];
    char *token;
    size_t capacity = 10;
    *count = 0;
    *records = malloc(capacity * sizeof(tInfractions));
    if (*records == NULL) {
        return NO_MEMORY;
    }

    // Lee la primera línea (encabezado)
    fgets(line, LINE, file);

    while (fgets(line, LINE, file) != NULL) {
        if (*count >= capacity) {
            capacity *= BLOCK;
            tInfractions *aux = realloc(*records, capacity * sizeof(tInfractions));
            if (aux == NULL) {
                free(*records);
                return NO_MEMORY;
            }
            *records = aux;
        }

        token = strtok(line, DELIMITER);
        (*records)[*count].id = atoi(token);

        token = strtok(NULL, END_LINE);
        strcpy((*records)[*count].description, token);

        (*count)++;
    }

    return OK;
}

void writeQuery1(FILE *file, tInfractions *records, size_t count) {
    for (size_t i = 0; i < count; i++) {
        fprintf(file, "%ld%s%s\n", records[i].id, DELIMITER, records[i].description);
    }
}
