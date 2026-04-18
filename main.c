#include <stdio.h>
#include "tablero.h"
#include <stdlib.h>
#include "piezas.h"
#include <time.h>
#include "armas.h"

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
    Tablero *t = tablero_crear(12, 12);
    Pieza *rey = crear_rey(t);
    Pieza *peon = crear_peon(t);
    Armas armas;
    armas.disparar[0] = escopeta;
    armas.disparar[1] = escopeta;
    armas.disparar[2] = escopeta;
    armas.disparar[3] = escopeta;

    //movimientos 
    char letra;
    
    while(1){
        imprimir_interfaz(1,1);
        tablero_imprimir(t);
        printf("\n> Ingrese accion: ");
        scanf("%c", &letra);

        //salida ddel juego
        if (letra == 'x'){ break; }

        //armas y su direccion
        if (letra >= '1' && letra <= '4'){
            int dx = 0, dy = 0;
            char direccion;
            printf("Direccion (w,a,s,d,q,e,z,c): ");
            scanf("%c", &direccion);
            if (direccion == 'w') dy = -1;
            if (direccion == 's') dy = 1;
            if (direccion == 'a') dx = -1;
            if (direccion == 'd') dx = 1;
            if (direccion == 'q'){dx = -1; dy = -1;}
            if (direccion == 'e'){dx = 1; dy = -1;}
            if (direccion == 'z'){dx = -1; dy = 1;}
            if (direccion == 'c'){dx = 1; dy = 1;}
            armas.disparar[letra - '1'](t, rey, dx, dy);
            continue;
        }

        //mov del rey
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

        //mov del pein
        mover_peon(t, peon, rey);

        //peon choca con rey
        if (peon->x == rey->x && peon->y == rey->y){
            printf("El rey ha sido alcanzado\n");
            break;
        }
    }
    free(peon);
    free(rey);
    tablero_liberar(t);
    printf("Juego Terminado\n");
    return 0;
}




