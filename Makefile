#
# Makefile para compilacion y ejecucion de los archivos
#

# FORMA PARAMETRIZADA
COMPILER=gcc
OUTPUT_FILE=prueba
FILES=front.c back.c
all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -Wall -pedantic -std=c99 -lm -g -fsanitize=address
clean:
	rm $(OUTPUT_FILE)