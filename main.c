#include <stdio.h>
#include "tablero.h"
#include <stdlib.h>
#include "piezas.h"
#include <time.h>

int main() {
    Tablero *t = tablero_crear(12, 12);

    srand(time(NULL));
    //rey
    Pieza *rey = malloc(sizeof(Pieza));
    rey->tipo = 'R';
    rey->hp = 10;
    int x = rand() % (t->W-2)+1;
    int y = t->H-1;
    rey->x = x;
    rey->y = y;
    t->celdas[y][x] = (void*) rey;

    //movimientos 
    char letra;
    printf("Movimiento: WASD | Diagonales: QEZC\n");
    printf("Armas: [1] Escopeta [2] Sniper [3] Granadas [4] Especial\n");
    printf("Salir: presione 'x'\n");
    
    while(1){
        printf("\n");
        tablero_imprimir(t);

        printf("\nIngrese accion (Movimiento o Arma 1-4): ");
        scanf("%c", &letra);

        if (letra == 'x'){
            break;
        }

        int x_nueva = rey->x;
        int y_nueva = rey->y;
        if (letra == 'w') y_nueva--;
        if (letra == 's') y_nueva++;
        if (letra == 'a') x_nueva--;
        if (letra == 'd') x_nueva++;
        if (letra == 'q'){x_nueva--; y_nueva--;}
        if (letra == 'e'){x_nueva++; y_nueva--;}
        if (letra == 'z'){x_nueva--; y_nueva++;}
        if (letra == 'c'){x_nueva++; y_nueva++;}
        
        if(x_nueva >=0 && x_nueva < t->W && y_nueva >= 0 && y_nueva < t->H){
            t->celdas[rey->y][rey->x] = NULL;
            rey->x = x_nueva;
            rey->y = y_nueva;
            t->celdas[rey->y][rey->x] = (void*) rey;
        }
    }
    free(rey);
    tablero_liberar(t);
    printf("Juego Terminado\n");
    return 0;
}




