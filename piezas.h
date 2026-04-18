#ifndef PIEZAS_H 
#define PIEZAS_H
#include <stdbool.h>
#include "tablero.h"

typedef struct {
    char tipo; /* 'P'=Peon, 'C'=Caballo, 'A'=Afil, 'T'=Torre, 'Q'=Reina, 'R'=Rey */
    int hp;
    int x, y;
} Pieza;

typedef struct {
    Pieza *pieza; /* NULL si la celda esta vacia */
} Celda;

Pieza* crear_rey(Tablero *t);
Pieza* crear_peon(Tablero *t);

void mover_peon(Tablero *t, Pieza *peon, Pieza *rey);
#endif

void spawn_nivel(struct Juego *juego, int nivel);
void mover_enemigos(struct Juego *juego);
bool verificar_estado_rey(struct Juego *juego); /* Revisa si el Rey esta en Jaque */