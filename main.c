#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

//interfaz
void imprimir_interfaz(Juego *j){
    printf("\n===================================================\n");
    if(j->nivel_actual == 1){
        printf("Nivel: 1 | Enemigos restantes: %d\n", j->turno_enemigos);
    }
    else if(j->nivel_actual ==2){
        printf("Nivel: 2 | Enemigos restantes: %d\n", j->turno_enemigos);
    }
    else if(j->nivel_actual ==3){
        printf("Nivel: 3 | Enemigos restantes: %d\n", j->turno_enemigos);
    }
    printf("Arsenal:\n");
    printf("[1] Escopeta (%d/%d)   ",
        j->arsenal.municion_actual[0],
        j->arsenal.municion_maxima[0]);
    printf("[2] Sniper (%d/%d)   ",
        j->arsenal.municion_actual[1],
        j->arsenal.municion_maxima[1]);
    printf("[3] Granada (%d/%d)   ",
        j->arsenal.municion_actual[2],
        j->arsenal.municion_maxima[2]);
    printf("[4] Especial (%d/%d)   ",
        j->arsenal.municion_actual[3],
        j->arsenal.municion_maxima[3]);
    printf("===================================================\n\n");
    printf("ACCIONES\n");
    printf("Disparo: [1-4]\n");          
    printf("Movimiento:\n");
    printf("[Q][W][E]\n");
    printf("[A]   [D]\n");
    printf("[Z][S][C]\n\n");

}
void avanzar_de_nivel(Juego *j){
    printf("\n====================================\n");
    printf("Nivel %d COMPLETADO!\n", j->nivel_actual);
    printf("El rey avanza al siguiente nivel\n");
    printf("Recuperando municion total\n");
    printf("\n====================================\n");
    j->nivel_actual++;
    if(j->nivel_actual >3){
        printf("GANASTE EL JUEGO\n");
        exit(0);
    }
    tablero_liberar(j->t);
    if(j->nivel_actual == 2) j->t = tablero_crear(8,8);
    if(j->nivel_actual == 3) j->t = tablero_crear(6,6);
    j->jugador = crear_rey(j->t);
    for(int i=0;i<4;i++){
        j->arsenal.municion_actual[i] = j->arsenal.municion_maxima[i];
    }
    spawn_nivel(j, j->nivel_actual);
}

int main() {
    srand(time(NULL));

    Juego *j = malloc(sizeof(Juego));
    j->t = tablero_crear(12,12);
    j->nivel_actual = 1;
    j->turno_enemigos = 0;
    j->jugador = crear_rey(j->t);

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
    spawn_nivel(j,1);

    //movimientos 
    char letra;
    
    while(1){
        imprimir_interfaz(j);
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
            if(dx==0 && dy==0){
                printf("Direccion invalida\n");
                continue;
            }

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
            if (letra == 'q'){nx--; ny--;}
            if (letra == 'e'){nx++; ny--;}
            if (letra == 'z'){nx--; ny++;}
            if (letra == 'c'){nx++; ny++;}
            if(nx >=0 && nx < j->t->W && ny >= 0 && ny < j->t->H){
                if(j->t->celdas[ny][nx] != NULL){
                    printf("Movimiento invalido (celda ocupada)\n");
                    continue;
                }
                j->t->celdas[j->jugador->y][j->jugador->x] = NULL;
                j->jugador->x = nx;
                j->jugador->y = ny;
                j->t->celdas[ny][nx] = (void*) j->jugador;
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

        //enemigos 
        mover_enemigos(j);

        //estado del rey
        if(verificar_estado_rey(j)){
            printf("El rey ha muerto\n");
            j->t->celdas[j->jugador->y][j->jugador->x] = NULL;
            break;
        }

        //vicorias
        if(j->turno_enemigos <=0){
            printf("Nivel completado exitosamente\n");
            avanzar_de_nivel(j);
        }

    }
    tablero_liberar(j->t);
    free(j);
    printf("Juego Terminado\n");
    return 0;
}




