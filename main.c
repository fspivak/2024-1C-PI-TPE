#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infractions.h"

#define LINE 100

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return FILE_NOT_FOUND;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error reading the file\nProgram terminated ...");
        return FILE_NOT_FOUND;
    }

    FILE *query1 = fopen("query1.csv", "w");
    if (query1 == NULL) {
        fprintf(stderr, "Error opening output file\nProgram terminated ...");
        fclose(file);
        return FILE_NOT_FOUND;
    }

    tInfractions *records;
    size_t count = 0;

    if (readInfractions(file, &records, &count) != OK) {
        fprintf(stderr, "Error reading infractions from file\nProgram terminated ...");
        fclose(file);
        fclose(query1);
        return NO_MEMORY;
    }

    writeQuery1(query1, records, count);

    free(records);
    fclose(file);
    fclose(query1);

    return OK;
}
