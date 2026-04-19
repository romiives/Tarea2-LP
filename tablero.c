#include "tablero.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "piezas.h"

/*
***
Parametro 1: int
Parametro 2: int
***
Tipo de Retorno: Tablero*
***
Crea un tablero dinamico detamño y ancho inicializado en null.
*/
Tablero* tablero_crear(int ancho, int alto) {
    Tablero *t = malloc(sizeof(Tablero));
    t->W = ancho;
    t->H = alto; 
    t->celdas = (void ***)malloc(alto * sizeof(void**));
    for (int i=0; i<alto; i++) {
        t->celdas[i] = (void **)malloc(ancho * sizeof(void*));
        for (int j=0; j<ancho; j++) {
            t->celdas[i][j] = NULL;
        }        
    }
    return t;
}

/*
***
Parametro 1: Tablero*
***
Tipo de Retorno: None
***
Imprime el tablero mostrando las piezas en sus posiciones.
*/
void tablero_imprimir(Tablero *t) {
    for (int i=0; i<t->H; i++) {
        printf("%2d ", t->H - i);
        for (int j=0; j<t->W;j++) {
            if(t->celdas[i][j] == NULL) {
                printf("[ ]");
            } else {
                Pieza *p = (Pieza*) t->celdas[i][j];
                printf("[%c]", p->tipo);
            }
        }
        printf("\n");
    }
    printf("   ");
    for (int j=1;j<=t->W;j++){
        printf(" %2d", j);
    }
    printf("\n");
}

/*
***
Parametro 1: Tablero*
Parametro 2: int
***
Tipo de Retorno: None
***
Imprime tablero con las posiciones afectadas por las armas.
*/
void tablero_con_disparo(Tablero *t, int disparo[t->H][t->W]){
    for(int i=0;i<t->H;i++){
        printf("%2d", t->H -i);
        for(int j=0;j<t->W;j++){
            if(disparo[i][j] == 1){
                printf("[X]");
            }
            else if(t->celdas[i][j]==NULL){
                printf("[ ]");
            }
            else{
                Pieza *p =(Pieza*) t->celdas[i][j];
                printf("[%c]", p->tipo);
            }
        }
        printf("\n");
    }
    printf("   ");
    for(int j=1;j<=t->W;j++) printf(" %2d", j);
    printf("\n");
}

/*
***
Parametro 1: Tablero*
***
Tipo de Retorno: None
***
Libera toda la memoria del tablero incluyendo piezas y las estructuras.
*/
void tablero_liberar(Tablero *t) {
    for(int i=0; i<t->H; i++){
        for(int j=0; j<t->W; j++){
            if(t->celdas[i][j] != NULL){
                free(t->celdas[i][j]);
                t->celdas[i][j] = NULL;
            }
        }
        free(t->celdas[i]);
    }
    free(t->celdas);
    free(t);
} 

