#include <stdio.h>
#include <stdlib.h>
#include "armas.h"
#include "main.h"

bool escopeta(struct Juego *j, int dx, int dy){
    int x = j->jugador->x;
    int y = j->jugador->y;
    printf("Escopeta dispara en (%d,%d)\n", dx, dy);
    for(int i=1; i<=3;i++){
        int bx = x + dx*i;
        int by = y + dy*i;
        for(int lado=-1; lado<=1; lado++){
            int ex = bx;
            int ey = by;
            if(dx !=0) ey += lado;
            if(dy !=0) ex += lado;
            if(ex<0 || ex>=j->t->W || ey<0 || ey>=j->t->H) continue;
            if (j->t->celdas[ey][ex] != NULL){
                Pieza *p =(Pieza*) j->t->celdas[ey][ex];
                if(p->tipo != 'R'){
                    int daño =(i==1) ? 2:1;
                    p->hp -= daño;
                    printf("Impacto a %c en (%d,%d) HP:%d\n", p->tipo, ex, ey, p->hp);
                    if(p->hp <=0){
                        free(p);
                        j->t->celdas[ey][ex] = NULL;
                        j->turno_enemigos--;
                        printf("Enemigo eliminado\n");
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
    printf("Sniper disparado en direccion (%d,%d)\n", dx, dy);
    while(1){
        x +=dx;
        y +=dy;
        if(x<0 || x>=j->t->W || y<0 || y>=j->t->H) break;
        if (j->t->celdas[y][x] != NULL){
            Pieza *p =(Pieza*) j->t->celdas[y][x];
            if(p->tipo != 'R'){
                p->hp -=3;
                printf("Impacto frnacotirador a %c en (%d,%d) HP:%d\n", p->tipo, x, y, p->hp);
                if(p->hp <= 0){
                    free(p);
                    j->t->celdas[y][x] = NULL;
                    j->turno_enemigos--;
                    printf("Enemigo eliminado\n");
                }
            }
            break;
        }
    }
    return true;
}

bool granada(struct Juego *j, int x, int y){
    int gx = j->jugador->x + x*3;
    int gy = j->jugador->y + y*3;
    printf("Granada lanzada hacia (%d,%d)\n", gx, gy);
    for(int i=-1; i<=1; i++){
        for(int k=-1; k<=1; k++){
            int x= gx + k;
            int y= gy + i;
            if(x<0 || x>=j->t->W || y<0 || y>=j->t->H) continue;
            if(j->t->celdas[y][x] !=NULL){
                Pieza *p=(Pieza*) j->t->celdas[y][x];
                if(p->tipo != 'R'){
                    p->hp -=2;
                    printf("Explosion golpea a %c en (%d,%d) HP:%d\n", p->tipo, x, y, p->hp);
                    if(p->hp <=0){
                        free(p);
                        j->t->celdas[y][x] = NULL;
                        j->turno_enemigos--;
                        printf("Enemigo eliminado\n");
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
