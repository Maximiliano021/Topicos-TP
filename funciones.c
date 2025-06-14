#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

void convertirFecha(Fecha *fechaOriginal, char *fechaConvertida){
  sprintf(fechaConvertida, "%04d-%02d-%02d", fechaOriginal->a, fechaOriginal->m, fechaOriginal->d);
}

Fecha parsearFecha(char *fechaStr){
  Fecha fecha;
  // Extraigo día, mes y año usando sscanf
  sscanf(fechaStr, "%d/%d/%d", &fecha.d, &fecha.m, &fecha.a);
  return fecha;
}

void procesarLinea(char *linea, char *lineaCorregida){
    char fechaStr[20];
    char *act;
    char fechaConvertida[12];
    int i = 0;

    // Busco la primera comilla y extraigo la fecha
    act = strchr(linea, '"');
    act++; // Salto la comilla

    // Copio la fecha hasta la siguiente comilla
    while (*act != '"') {
        fechaStr[i] = *act;
        act++;
        i++;
    }
    
    fechaStr[i] = '\0';

    // Busco el resto de la línea después del primer punto y coma
    act = strchr(linea, ';');
    act++; // Salto el punto y coma

    // Parseo la fecha original
    Fecha fechaOriginal = parsearFecha(fechaStr);

    // Convierto la fecha al nuevo formato
    convertirFecha(&fechaOriginal, fechaConvertida);

    // Construyo la línea corregida
    sprintf(lineaCorregida, "\"%s\";%s", fechaConvertida, act);
}
