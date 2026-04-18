#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

//interfaz
void imprimir_interfaz(int nivel, int enemigos){
    printf("\n===================================================\n");
    printf("Nivel: %d | Enemigos restantes: %d\n", nivel, enemigos);
    printf("Arsenal: [1] Escopeta [2] Sniper [3] Granada [4] Especial\n");
    printf("=============================================\n\n");
    printf("ACCIONES DISPONIBLES\n");
    printf("Disparo: [1-4]\n");
    printf("Movimiento:\n");
    printf("[Q][W][E]\n");
    printf("[A]   [D]\n");
    printf("[Z][S][C]\n\n");

}

int main() {
    srand(time(NULL));

    Juego *j = malloc(sizeof(Juego));
    j->t = tablero_crear(12,12);
    j->jugador = crear_rey(j->t);
    Pieza *peon = crear_peon(j->t);
    j->nivel_actual = 1;
    j->turno_enemigos = 0;
    
    //armas
    j->arsenal.disparar[0] = escopeta;
    j->arsenal.disparar[1] = francotirador;
    j->arsenal.disparar[2] = granada;
    j->arsenal.disparar[3] = especial;

    //movimientos 
    char letra;
    
    while(1){
        imprimir_interfaz(j->nivel_actual, 1);
        tablero_imprimir(j->t);
        printf("\n> Ingrese accion: ");
        scanf(" %c", &letra);

        //salida ddel juego
        if (letra == 'x'){ break; }

        //armas y su direccion
        if (letra >= '1' && letra <= '4'){
            int dx = 0, dy = 0;
            char direccion;
            printf("Direccion (w,a,s,d,q,e,z,c): ");
            scanf(" %c", &direccion);
            if (direccion == 'w') dy = -1;
            if (direccion == 's') dy = 1;
            if (direccion == 'a') dx = -1;
            if (direccion == 'd') dx = 1;
            if (direccion == 'q'){dx = -1; dy = -1;}
            if (direccion == 'e'){dx = 1; dy = -1;}
            if (direccion == 'z'){dx = -1; dy = 1;}
            if (direccion == 'c'){dx = 1; dy = 1;}
            j->arsenal.disparar[letra - '1'](j, dx, dy);
            continue;
        }

        //mov del rey
        int x_nueva = j->jugador->x;
        int y_nueva = j->jugador->y;
        if (letra == 'w') y_nueva--;
        if (letra == 's') y_nueva++;
        if (letra == 'a') x_nueva--;
        if (letra == 'd') x_nueva++;
        if (letra == 'q'){x_nueva--; y_nueva--;}
        if (letra == 'e'){x_nueva++; y_nueva--;}
        if (letra == 'z'){x_nueva--; y_nueva++;}
        if (letra == 'c'){x_nueva++; y_nueva++;}
        
        if(x_nueva >=0 && x_nueva < j->t->W && y_nueva >= 0 && y_nueva < j->t->H){
            j->t->celdas[j->jugador->y][j->jugador->x] = NULL;
            j->jugador->x = x_nueva;
            j->jugador->y = y_nueva;
            j->t->celdas[j->jugador->y][j->jugador->x] = (void*) j->jugador;
        }

        //mov del pein
        mover_peon(j->t, peon, j->jugador);

        //peon choca con rey
        if (peon->x == j->jugador->x && peon->y == j->jugador->y){
            printf("El rey ha sido alcanzado\n");
            break;
        }
    }
    free(peon);
    free(j->jugador);
    tablero_liberar(j->t);
    free(j);
    printf("Juego Terminado\n");
    return 0;
}




