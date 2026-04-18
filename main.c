#include <stdio.h>
#include "tablero.h"
#include <stdlib.h>
#include "piezas.h"
#include <time.h>

int main() {

    Tablero *t = tablero_crear(12, 12);

    srand(time(NULL));
    Pieza *rey = malloc(sizeof(Pieza));
    rey->tipo = 'R';
    rey->hp = 10;
    int x = rand() % (t->W-2)+1;
    int y = t->H-1;
    rey->x = x;
    rey->y = y;
    
    t->celdas[y][x] = (void*) rey;

    printf("Tablero creado\n");
    tablero_imprimir(t);
    tablero_liberar(t);
    
    return 0;
}