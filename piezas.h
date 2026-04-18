#ifndef PIEZAS_H 
#define PIEZAS_H
#include <stdbool.h>
#include "tablero.h"

struct Juego;
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
Pieza* crear_caballo(Tablero *t);
Pieza* crear_alfil(Tablero *t);
Pieza* crear_torre(Tablero *t);
Pieza* crear_reina(Tablero *t);

void spawn_nivel(struct Juego *juego, int nivel);
void mover_enemigos(struct Juego *juego);
bool verificar_estado_rey(struct Juego *juego); /* Revisa si el Rey esta en Jaque */

void mover_peon(Tablero *t, Pieza *peon, Pieza *rey);
void mover_caballo(Tablero *t, Pieza *p, Pieza *rey);
void mover_alfil(Tablero *t, Pieza *p, Pieza *rey);
void mover_torre(Tablero *t, Pieza *p, Pieza *rey, int turno);
void mover_reina(Tablero *t, Pieza *p, Pieza *rey);

#endif

