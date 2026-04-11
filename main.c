#include <stdio.h>
#include "tablero.h"

int main() {

    Tablero *t = tablero_crear(5, 5);

    printf("Tablero creado\n");

    tablero_liberar(t);
    tablero_imprimir(t);
    return 0;
}