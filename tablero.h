#ifndef TABLERO_H
#define TABLERO_H

struct Juego;
typedef struct {
    int W, H;
    void ***celdas; /* celdas[y][x] apunta a Celda* */
} Tablero;

Tablero* tablero_crear(int ancho, int alto);
void tablero_liberar(Tablero *tablero); /* debe limpiar la memoria heap */
void tablero_imprimir(Tablero *tablero);

#endif 