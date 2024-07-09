# 2024-1C-PI-TPE

## Descripción
Diseñar e implementar un programa para el procesamiento de datos de multas de estacionamiento, basado en datos reales. Obteniendo como resultado:
Query 1: Total de multas por infraccion
Query 2: Infracción más popular por agencia emisora
Query 3: Patente con más multas por infracción 

## Lista de Archivos Fuente y de Encabezado

**Archivos fuente (.c):**
- `mainCHI.c`: Contiene la función principal del programa para analizar los archivos de Chicago (CHI).
- `mainNYC.c`: Contiene la función principal del programa para analizar los archivos de Nueva York (NYC).
- `infractionsADT.c`: Implementa las funciones relacionadas con la estructura de datos `infractionsADT` para la lectura y análisis de los archivos de infracciones.
- `tickets.c`: Implementa las funciones y tipos relacionados con tickets para la lectura, análisis y posterior escritura de los archivos y queries.
- `bagADT.c`: Archivo para el manejo del back-end del Query 1 (Total de multas por infracción). Maneja un bag de elementos genéricos en forma de vector para luego ordenarlo por cantidad de apariciones de cada elemento.
- `bookADT.c`: Archivo para el manejo del back-end del Query 2 (Infracción más popular por agencia emisora).
- `dictADT.c`: Archivo para el manejo del front-end del Query 3 (Patente con más multas por infracción).

**Archivos de encabezado (.h):**
- `infractionsADT.h`: Declara las funciones y tipos relacionados con `infractionsADT` para la lectura y análisis de los archivos de infracciones.
- `tickets.h`: Declara las funciones y tipos relacionados con tickets para la lectura, análisis y posterior escritura de los archivos y queries.
- `bagADT.h`: Header para el manejo del back-end del Query 1 (Total de multas por infracción). Manejo de un bag de elementos genéricos en forma de vector para luego ordenarlo por cantidad de apariciones de cada elemento.
- `bookADT.h`: Header para el manejo del back-end del Query 2 (Infracción más popular por agencia emisora).
- `dictADT.h`: Header para el manejo del front-end del Query 3 (Patente con más multas por infracción).

**Otros archivos:**
- `Makefile`: Makefile para compilación y ejecución de los archivos.
- `.git`: Donde se detallan todas las modificaciones realizadas



## Comandos necesarios para compilar el proyecto

Para compilar todo el proyecto para el uso de datos de Nueva York:
```sh = 
make nyc
```

Para generar los Query de Nueva York deseados (del 1 al 3 por ser un único integrado), asegúrate de que los archivos ticketsNYC.csv e infractionsNYC.csv estén en el mismo    directorio que el ejecutable:
```sh = 
make querynyc
```

Para compilar todo el proyecto para el uso de datos de Chicago:
```sh = 
make chi
```

Para generar los Query de Chicago deseados (del 1 al 3 por ser un único integrado), asegúrate de que los archivos ticketsCHI.csv e infractionsCHI.csv estén en el mismo    directorio que el ejecutable:
```sh = 
make querynyc
```


## Autor del Proyecto
Federico Spivak

## Información de contacto
fespivak@itba.edu.ar
