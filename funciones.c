#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Convierte la fecha a aa-mm-dd
Fecha parsearFecha(char *fechaStr)
{
    Fecha fecha;

    // Formateo la fecha dependiendo del formato
    if (strchr(fechaStr, '-') != NULL)
    {
        sscanf(fechaStr, "%d-%d-%d", &fecha.a, &fecha.m, &fecha.d);
    }
    else
    {
        sscanf(fechaStr, "%d/%d/%d", &fecha.d, &fecha.m, &fecha.a);
    }

    return fecha;
}

// Procesa una línea del archivo, extrayendo la fecha y el resto de la información
void procesarLinea(char *linea, char *lineaCorregida)
{
    char fechaStr[20];
    char *act;
    char fechaConvertida[12];
    int i = 0;

    // Busco la primera comilla y extraigo la fecha
    act = strchr(linea, '"');
    act++; // Salto la comilla

    // Copio la fecha hasta la siguiente comilla
    while (*act != '"')
    {
        fechaStr[i] = *act;
        act++;
        i++;
    }

    fechaStr[i] = '\0';

    // Busco el resto de la línea después del primer punto y coma
    act = strchr(linea, ';');
    act++; // Salto el punto y coma

    // Copio el resto de la línea
    char restoLinea[TAM_LINEA];
    strcpy(restoLinea, act);

    // Convierto comas a puntos en el resto de la línea (para el índice)
    convertirComaAPunto(restoLinea);

    // Parseo la fecha original
    Fecha fechaOriginal = parsearFecha(fechaStr);

    // Especifica el formato de la fecha
    sprintf(fechaConvertida, "%04d-%02d-%02d", fechaOriginal.a, fechaOriginal.m, fechaOriginal.d);

    // Construyo la línea corregida
    sprintf(lineaCorregida, "\"%s\";%s", fechaConvertida, restoLinea);
}

// Convierte comas a puntos en el string dado
void convertirComaAPunto(char *indice)
{
    char *act = indice;

    // Recorro el string buscando comas
    while (*act != '\0')
    {
        // Si encuentro una coma, la cambio por punto
        if (*act == ',')
        {
            *act = '.';
        }
        act++;
    }
}
