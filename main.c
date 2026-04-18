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
    //municion
    j->arsenal.municion_maxima[0] = 2;
    j->arsenal.municion_maxima[1] = 1;
    j->arsenal.municion_maxima[2] = 2;
    j->arsenal.municion_maxima[3] = 3;
    //muncion actual
    for(int i=0; i<4;i++){
        j->arsenal.municion_actual[i] = j->arsenal.municion_maxima[i];
    }

    //movimientos 
    char letra;
    
    while(1){
        imprimir_interfaz(j->nivel_actual, 1);
        tablero_imprimir(j->t);
        printf("\n> Ingrese accion: ");
        scanf(" %c", &letra);

        //salida ddel juego
        if (letra == 'x'){ break; }

        int accion_valida =0;
        //armas y disparo
        if (letra >= '1' && letra <= '4'){
            int arma = letra - '1';
            if(j->arsenal.municion_actual[arma]<=0){
                printf("Sin municion\n");
                continue;
            }
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
            j->arsenal.disparar[arma](j,dx, dy);
            j->arsenal.municion_actual[arma]--;
            accion_valida = 1;
        }

        //mov 
        if (letra == 'w' || letra == 'a' || letra == 's' || letra == 'd' || letra == 'q' || letra == 'e' || letra == 'z' || letra == 'c'){
            int nx = j->jugador->x;
            int ny = j->jugador->y;
            if (letra == 'w') ny--;
            if (letra == 's') ny++;
            if (letra == 'a') nx--;
            if (letra == 'd') nx++;
            if (letra == 'q'){nx--; nx--;}
            if (letra == 'e'){nx++; ny--;}
            if (letra == 'z'){nx--; ny++;}
            if (letra == 'c'){nx++; ny++;}
            if(nx >=0 && nx < j->t->W && ny >= 0 && ny < j->t->H){
                j->t->celdas[j->jugador->y][j->jugador->x] = NULL;
                j->jugador->x = nx;
                j->jugador->y = ny;
                j->t->celdas[ny][nx] = j->jugador;
                if(j->arsenal.municion_actual[0] < j->arsenal.municion_maxima[0]){
                    j->arsenal.municion_actual[0]++;
                }
                accion_valida =1;
            }  
        }
        if (!accion_valida){
            printf("Accion Invalida\n");
            continue;
        }
        
        //mov del pein
        mover_peon(j->t, peon, j->jugador);

        //peon choca con rey
        if (peon->x == j->jugador->x && peon->y == j->jugador->y){
            printf("El rey ha sido alcanzado\n");
            j->t->celdas[j->jugador->y][j->jugador->x] = NULL;
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




