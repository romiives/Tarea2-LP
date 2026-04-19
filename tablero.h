#ifndef TABLERO_H
#define TABLERO_H

typedef struct {
    int W, H;
    void ***celdas; /* celdas[y][x] apunta a Celda* */
} Tablero;

Tablero* tablero_crear(int ancho, int alto);
void tablero_imprimir(Tablero *tablero);
void tablero_con_disparo(Tablero *t, int disparo[t->H][t->W]);
void tablero_liberar(Tablero *tablero); /* debe limpiar la memoria heap */

#endif 