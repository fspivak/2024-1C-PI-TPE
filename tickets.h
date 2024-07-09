#ifndef TICKETS_H
#define TICKETS_H

#include "infractionsADT.h"

typedef enum {NYC=0, CHI} city;

/* Lee los tickets desde un archivo CSV, los analisa y crea los query csv de salida */
status readTickets(FILE *file, infractionsADT infractions, city c);

#endif // TICKETS_H
