#include <stdio.h>
#include "tablero.h"
#include <stdlib.h>
#include "piezas.h"

int main() {

    Tablero *t = tablero_crear(5, 5);

    Pieza *rey = malloc(sizeof(Pieza));
    rey->tipo = 'R'
    rey->hp = 10;
    rey->x = 2;
    rey->y = 4;
    t->celdas[rey->y][rey->x] = rey;
    
    printf("Tablero creado\n");
    tablero_imprimir(t);
    tablero_liberar(t);
    
    return 0;
}