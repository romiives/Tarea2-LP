#include <stdlib.h>
#include <time.h>
#include "piezas.h"

//creacion del rey en la ultima fila
Pieza* crear_rey(Tablero *t){
    Pieza *rey = malloc(sizeof(Pieza));
    rey->tipo = 'R';
    rey->hp = 10;
    int x = rand() % (t->W-2)+1;
    int y = t->H-1;
    rey->x = x;
    rey->y = y;
    t->celdas[y][x] = (void*) rey;
    return rey;
}

//creacion del peon en fila 2
Pieza* crear_peon(Tablero *t){
    Pieza *peon = malloc(sizeof(Pieza));
    peon->tipo = 'P';
    peon->hp = 1;
    int x = rand() % t->W;
    int y = 1;
    peon->x = x;
    peon->y = y;
    t->celdas[y][x] = (void*) peon;
    return peon;
}

//movimiento del peon hacia el rey
void mover_peon(Tablero *t, Pieza *peon, Pieza *rey){
    t->celdas[peon->y][peon->x] = NULL;
    if(peon->x < rey->y) peon->x++;
    else if (peon->x > rey->x) peon->x--;
    if(peon->y < rey->y) peon->y++;
    else if(peon->y > rey->y) peon->y--;
    t->celdas[peon->y][peon->x] = (void*) peon;
}