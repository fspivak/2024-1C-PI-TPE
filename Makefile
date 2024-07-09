#
# Makefile para compilacion y ejecucion de los archivos
#

# FORMA PARAMETRIZADA
COMPILER=gcc

OUTPUT_FILE_NYC=parkingTicketsNYC
OUTPUT_FILE_CHI=parkingTicketsCHI

FILES_NYC=mainNYC.c infractionsADT.c tickets.c bagADT.c bookADT.c dictADT.c
FILES_CHI=mainCHI.c infractionsADT.c tickets.c bagADT.c bookADT.c dictADT.c

FLAGS=-Wall -pedantic -std=c99 -lm -g -fsanitize=address


nyc:
	$(COMPILER) -o $(OUTPUT_FILE_NYC) $(FILES_NYC) $(FLAGS)

chi:
	$(COMPILER) -o $(OUTPUT_FILE_CHI) $(FILES_CHI) $(FLAGS)

querynyc:
	./$(OUTPUT_FILE_NYC) ticketsNYC.csv infractionsNYC.csv 

querychi:
	./$(OUTPUT_FILE_CHI) ticketsCHI.csv infractionsCHI.csv 

clean:
	rm $(OUTPUT_FILE)