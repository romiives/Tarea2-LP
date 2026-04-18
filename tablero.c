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

void tablero_imprimir(Tablero *tablero) {
    for (int i=0; i<tablero->H; i++) {
        printf("%2d", tablero->H-i);
        for (int j=0; j<tablero->W;j++) {
            if(tablero->celdas[i][j] == NULL) {
                printf("[ ]");
            } else {
                Pieza *p = (Pieza*) tablero->celdas[i][j];
                printf("[%c]", p->tipo);
            }
        }
        printf("\n");
    }
    printf(" ");
    for (int j=1;j<=tablero->W;j++){
        printf("%d", j);
    }
    printf("\n");
}

void tablero_liberar(Tablero *tablero) {
    for(int i=0; i<tablero->H; i++){
        free(tablero->celdas[i]);
    }
    free(tablero->celdas);
    free(tablero);
} 

