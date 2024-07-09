#include "tickets.h"
#include "infractionsADT.h"
#include "bagADT.h"
#include "bookADT.h"
#include "dictADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipos de funciones auxiliares
static status processLineNYC(char *line, infractionsADT infractions, bagADT bag1, bookADT book2, dictADT dict3);
static status processLineCHI(char *line, infractionsADT infractions, bagADT bag1, bookADT book2, dictADT dict3);
static status writeQuery1(bagADT bag1);
static status writeQuery2(bookADT book2);
static status writeQuery3(dictADT dict3);

status readTickets(FILE *file, infractionsADT infractions, city c) {
    status flag1 = OK;
    status flag2 = OK;
    status flag3 = OK;
    char line[LINE];

    bagADT bag1 = newBag(&flag1);
    bookADT book2 = newBook(&flag2);
    dictADT dict3 = newDict(getInfractions(infractions), sizeInfractions(infractions), &flag3);

    if (flag1!=OK||flag2!=OK||flag3!=OK ) {
        return NO_MEMORY;
    }

    fgets(line, LINE, file); // Leer la primera línea (encabezado)

    while (fgets(line, LINE, file) != NULL) {
        flag1 = ((c==NYC)?processLineNYC(line, infractions, bag1, book2, dict3):processLineCHI(line, infractions, bag1, book2, dict3));
        if (flag1 != OK) {
            return flag1;
        }
    }

    flag1 = writeQuery1(bag1);
    flag2 = writeQuery2(book2);
    flag3 = writeQuery3(dict3);

    if (flag1!=OK||flag2!=OK||flag3!=OK ) {
        return NO_MEMORY;
    }

    return OK;
}

static status processLineNYC(char *line, infractionsADT infractions, bagADT bag1, bookADT book2, dictADT dict3) {
    status flag1 = OK;
    status flag2 = OK;
    status flag3 = OK;
    char *token;
    tRecordTicketNYC record;

    token = strtok(line, DELIMITER);
    strcpy(record.plate, token);

    strtok(NULL, DELIMITER); // issueDate
    token = strtok(NULL, DELIMITER);
    record.infractionId = atoi(token);

    strtok(NULL, DELIMITER); // fineAmount
    token = strtok(NULL, END_LINE);
    strcpy(record.issuingAgency, token);

    // Validar infractionId
    if (belongsInfractions(infractions, record.infractionId)) {
        flag1 = addBag(bag1, findInfraction(infractions, record.infractionId));
        flag2 = addBook(book2, record.issuingAgency, findInfraction(infractions, record.infractionId));
        flag3 = addDict(dict3, record.infractionId, record.plate);

        if (flag1!=OK||flag2!=OK||flag3!=OK ) {
        return NO_MEMORY;
        }
    }

    return OK;
}

static status processLineCHI(char *line, infractionsADT infractions, bagADT bag1, bookADT book2, dictADT dict3) {
    status flag1 = OK;
    status flag2 = OK;
    status flag3 = OK;
    char *token;
    tRecordTicketCHI record;

    strtok(line, DELIMITER); // issueDate

    token = strtok(NULL, DELIMITER);
    strcpy(record.plateRedacted, token);

    token = strtok(NULL, DELIMITER);
    strcpy(record.unitDescription, token);

    token = strtok(NULL, DELIMITER);
    record.infractionCode = atoi(token);

    // Validar infractionId
    if (belongsInfractions(infractions, record.infractionCode)) {
        flag1 = addBag(bag1, findInfraction(infractions, record.infractionCode));
        flag2 = addBook(book2, record.unitDescription, findInfraction(infractions, record.infractionCode));
        flag3 = addDict(dict3, record.infractionCode, record.plateRedacted);

        if (flag1!=OK||flag2!=OK||flag3!=OK ) {
        return NO_MEMORY;
        }
    }

    return OK;
}

static status writeQuery1(bagADT bag1) {
    FILE *fileQuery1 = fopen("query1.csv", "w");
    if (fileQuery1 == NULL) {
        return NO_MEMORY;
    }

    sortBag(bag1);
    tQueryBag1 query1;
    for (size_t i = 0; i < sizeBag(bag1); i++) {
        query1 = getElemBag(bag1, i);
        fprintf(fileQuery1, "%s%s%ld\n", query1.elem, DELIMITER, query1.count);
    }
    fclose(fileQuery1);
    freeBag(bag1);
    return OK;
}

static status writeQuery2(bookADT book2) {
    FILE *fileQuery2 = fopen("query2.csv", "w");
    if (fileQuery2 == NULL) {
        return NO_MEMORY;
    }

    tQueryBook2 query2;
    toBeginMostPopular(book2);
    while (hasNextMostPopular(book2)) {
        query2 = nextMostPopular(book2);
        fprintf(fileQuery2, "%s%s%s%s%ld\n", query2.group, DELIMITER, query2.cat, DELIMITER, query2.count);
    }
    fclose(fileQuery2);
    freeBook(book2);
    return OK;
}

static status writeQuery3(dictADT dict3) {
    FILE *fileQuery3 = fopen("query3.csv", "w");
    if (fileQuery3 == NULL) {
        return NO_MEMORY;
    }

    tQueryDict3 query3;
    for (size_t i = 0; i < sizeDict(dict3); i++) {
        query3 = getElemMostPopularDict(dict3, i);
        if (query3.elem != NULL) {
            fprintf(fileQuery3, "%s%s%s%s%ld\n", query3.elem, DELIMITER, query3.cat, DELIMITER, query3.count);
        }
    }
    fclose(fileQuery3);
    freeDict(dict3);
    return OK;
}
