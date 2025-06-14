#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main() {
    FILE *pf;
    FILE *pfTemp;
    char linea[TAM_LINEA];
    char lineaCorregida[TAM_LINEA];
    int contador = 0;
    
    // Abro el archivo original
    pf = fopen("indices_icc_general_capitulos.csv", "r");
    if (!pf) {
        printf("Error en apertura\n");
        return ERROR_ARCH;
    }
    
    // Creo archivo temporal
    pfTemp = fopen("temp.csv", "w");
    if (!pfTemp) {
        fclose(pf);
        return ERROR_ARCH;
    }
    
    // Copio la primera línea (encabezados) sin modificar
    fgets(linea, TAM_LINEA, pf);
    fprintf(pfTemp, "%s", linea);
    
    // Proceso cada línea del archivo
    while (fgets(linea, TAM_LINEA, pf)) {
        // Proceso la línea
        procesarLinea(linea, lineaCorregida);
        
        // Escribo la línea corregida
        fprintf(pfTemp, "%s", lineaCorregida);
        
        // Incremento contador
        contador++;
    }
    
    // Cierro archivos
    fclose(pf);
    fclose(pfTemp);
    
    // Reemplazo el archivo original
    remove("indices_icc_general_capitulos.csv");
    rename("temp.csv", "indices_icc_general_capitulos.csv");
    
    // Muestro resultado
    printf("Proceso completado. %d registros corregidos\n", contador);
    
    return TODO_OK;
}