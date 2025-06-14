#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

#define ARCHIVO1 "indices_icc_general_capitulos.csv"
#define ARCHIVO2 "indices_items_obra.csv"

int main()
{
    FILE *pf;
    FILE *pfTemp;
    char linea[TAM_LINEA];
    char lineaCorregida[TAM_LINEA];
    int contador = 0;
    int opcion;
    const char *archivoSeleccionado;

    printf("=== Parseo de fecha e indice ===\n");
    printf("1- %s\n", ARCHIVO1);
    printf("2- %s\n", ARCHIVO2);
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch(opcion)
    {
    case 1:
        archivoSeleccionado = ARCHIVO1;
        break;
    case 2:
        archivoSeleccionado = ARCHIVO2;
        break;
    default:
        printf("Opcion invalida.\n");
        return 1;
    }


    // Abro el archivo original
    pf = fopen(archivoSeleccionado, "r");
    if (!pf)
    {
        printf("Error en apertura\n");
        return ERROR_ARCH;
    }

    // Creo archivo temporal
    pfTemp = fopen("temp.csv", "w");
    if (!pfTemp)
    {
        fclose(pf);
        return ERROR_ARCH;
    }

    // Copio la primera línea (encabezados) sin modificar
    fgets(linea, TAM_LINEA, pf);
    fprintf(pfTemp, "%s", linea);

    // Proceso cada línea del archivo
    while (fgets(linea, TAM_LINEA, pf))
    {
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
    remove(archivoSeleccionado);
    rename("temp.csv", archivoSeleccionado);

    // Muestro resultado
    printf("\n\nProceso completado", contador);

    return TODO_OK;
}
