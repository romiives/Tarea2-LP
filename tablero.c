#include "tablero.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "piezas.h"


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

void tablero_imprimir(Tablero *t) {
    for (int i=t->H - 1; i>=0; i--) {
        printf("%2d", i + 1);
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
        printf("%d", j);
    }
    printf("\n");
}

void tablero_con_disparo(Tablero *t, int disparo[20][20]){
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
    for(int j=1;j<=t->W;j++) printf("%d", j);
    printf("\n");
}

void tablero_liberar(Tablero *t) {
    for(int i=0; i<t->H; i++){
        free(t->celdas[i]);
    }
    free(t->celdas);
    free(t);
} 

