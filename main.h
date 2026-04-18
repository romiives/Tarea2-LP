#ifndef MAIN_H
#define MAIN_H
#include "tablero.h"
#include "piezas.h"
#include "armas.h"

typedef struct {
    Tablero *t;
    Armas arsenal;
    Pieza *jugador; /* El Rey */
    int nivel_actual; /* 1, 2 o 3 */
    int turno_enemigos; /* Contador para gestionar piezas lentas como la Torre */
} Juego;

#endif