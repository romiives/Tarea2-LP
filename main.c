#include <stdio.h>
#include "tablero.h"

int main() {

    struct Tablero *t = tablero_crear(5, 5);

    printf("Tablero creado\n");

    tablero_liberar(t);

    return 0;
}