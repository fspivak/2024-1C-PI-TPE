#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "infractionsADT.h"
#include "tickets.h"

#define FILES_INPUT 2

int main(int argc, char *argv[]) {
    status flag = OK; //Flag para errores dentro de los TADs

    // Check de manejo de archivos de entrada/salida
    if (argc != FILES_INPUT + 1) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return FILE_NOT_FOUND;
    }

    FILE *fileInfractions = fopen(argv[2], "r");
    if (fileInfractions == NULL) {
        fprintf(stderr, "Error accessing infractions file\nProgram terminated ...");
        return FILE_NOT_FOUND;
    }

    infractionsADT infractions = newInfractions(&flag);
    if (flag != OK) {
        fprintf(stderr, "Memory allocation error\nProgram terminated ...");
        fclose(fileInfractions);
        return NO_MEMORY;
    }

    if (readInfractions(fileInfractions, infractions) != OK) {
        fprintf(stderr, "Error reading infractions from file\nProgram terminated ...");
        fclose(fileInfractions);
        freeInfractions(infractions);
        return NO_MEMORY;
    }

    fclose(fileInfractions); // No uso mas el csv de fileInfractions

    FILE *fileTickets = fopen(argv[1], "r");
    if (fileTickets == NULL) {
        fprintf(stderr, "Error accessing tickets file\nProgram terminated ...");
        freeInfractions(infractions);
        return FILE_NOT_FOUND;
    }

    if (readTickets(fileTickets, infractions, NYC) != OK) {
        fprintf(stderr, "Error reading tickets from file\nProgram terminated ...");
        fclose(fileTickets);
        freeInfractions(infractions);
        return NO_MEMORY;
    }

    fclose(fileTickets);

    freeInfractions(infractions);

    return OK;
}
