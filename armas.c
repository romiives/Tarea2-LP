#include <stdio.h>
#include <stdlib.h>
#include "armas.h"
#include "main.h"

bool escopeta(struct Juego *j, int dx, int dy){
    int x = j->jugador->x;
    int y = j->jugador->y;
    for(int i=1; i<=3;i++){
        int bx = x + dx*i;
        int by = y + dy*i;
        for(int lado=-1; lado<=1; lado++){
            int ex = bx;
            int ey = by;
            if(dx !=0) ey += lado;
            if(dy !=0) ex += lado;
            if(ex<0 || ex>=j->t->W || ey<0 || ey>=j->t->H) break;
            if (j->t->celdas[ey][ex] != NULL){
                Pieza *p =(Pieza*) j->t->celdas[ey][ex];
                if(p->tipo != 'R'){
                    int daño =(i==1) ? 2:1;
                    p->hp -= daño;
                    if(p->hp <=0){
                        free(p);
                        j->t->celdas[ey][ex] = NULL;
                        j->turno_enemigos--;
                    }
                }
            }
        }
    }
    return true;
}

bool francotirador(struct Juego *j, int dx, int dy){
    int x = j->jugador->x;
    int y = j->jugador->y;
    while(1){
        x +=dx;
        y +=dy;
        if(x<0 || x>=j->t->W || y<0 || y>=j->t->H) break;
        if (j->t->celdas[y][x] != NULL){
            Pieza *p =(Pieza*) j->t->celdas[y][x];
            if(p->tipo != 'R'){
                p->hp -=3;
                if(p->hp <= 0){
                    free(p);
                    j->t->celdas[y][x] = NULL;
                    j->turno_enemigos--;
                }
            }
            break;
        }
    }
    return true;
}

bool granada(struct Juego *j, int x, int y){
    int gx = j->jugador->x + dx*3;
    int gy = j->jugador->y + dy*3;
    for(int i=-1; i<=1; i++){
        for(int k=-1; k<=1; k++){
            int x= gx + k;
            int y= gy + i;
            if(x<0 || x>=j->t->W || y<0 || y>=j->t->H) continue;
            if(j->t->celdas[y][x] !=NULL){
                Pieza *p=(Pieza*) j->t->celdas[y][x];
                if(p->tipo != 'R'){
                    p->hp -=2;
                    if(p->hp <=0){
                        free(p);
                        j->t->celdas[y][x] = NULL;
                        j->turno_enemigos--;
                    }
                }
            }
        }
    }
    return true;
}
bool especial(struct Juego *j, int dx, int dy){
    printf("Arma Especial\n");
    (void)j;
    (void)dx;
    (void)dy;
    return true;
}
