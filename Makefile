#
# Makefile para compilacion y ejecucion de los archivos
#

# FORMA PARAMETRIZADA
COMPILER=gcc
OUTPUT_FILE=prueba
FILES_BAGADT=bagADT_Test.c bagADT.c
FILES_BOOKADT=bookADT_Test.c bookADT.c
FILES_NYC=mainNYC.c infractionsADT.c tickets.c bagADT.c bookADT.c dictADT.c
FILES_CHI=mainCHI.c infractionsADT.c tickets.c bagADT.c bookADT.c dictADT.c

bag:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES_BAGADT) -Wall -pedantic -std=c99 -lm -g -fsanitize=address
book:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES_BOOKADT) -Wall -pedantic -std=c99 -lm -g -fsanitize=address

nyc:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES_NYC) -Wall -pedantic -std=c99 -lm -g -fsanitize=address

chi:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES_CHI) -Wall -pedantic -std=c99 -lm -g -fsanitize=address

querynyc:
	./$(OUTPUT_FILE) ticketsNYC_Test.csv Dataset\ Alumnos/infractionsNYC.csv 

querychi:
	./$(OUTPUT_FILE) ticketsCHI_Test.csv Dataset\ Alumnos/infractionsNYC.csv 

clean:
	rm $(OUTPUT_FILE)