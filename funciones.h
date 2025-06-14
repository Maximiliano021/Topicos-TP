#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define ERROR_ARCH 0
#define TODO_OK 1
#define TAM_LINEA 200

typedef struct {
    int d;
    int m;
    int a;
} Fecha;

// Convierte fecha dia/mes/año a año-mes-dia
void convertirFecha(Fecha *fechaOriginal, char *fechaConvertida);

Fecha parsearFecha(char *fechaStr);

void procesarLinea(char *linea, char *lineaCorregida);

#endif // FUNCIONES_H_INCLUDED
