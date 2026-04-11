#include <stdio.h>
#include "tablero.h"

int main() {

    Tablero *t = tablero_crear(5, 5);

    printf("Tablero creado\n");

    return 0;
}