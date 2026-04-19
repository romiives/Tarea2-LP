#include <stdio.h>
#include <stdlib.h>
#include "armas.h"
#include "main.h"
#include "tablero.h"

bool escopeta(struct Juego *j, int dir_x, int dir_y){
    int disparo[20][20] = {0};
    int x = j->jugador->x;
    int y = j->jugador->y;
    printf("Escopeta dispara en (%d,%d)\n", dir_x, dir_y);
    int impacto_x = -1;
    int impacto_y = -1;
    for(int i=1; i<=3;i++){
        int nx = x + dir_x*i;
        int ny = y + dir_y*i;
        if(nx<0 || nx>=j->t->W || ny<0 || ny>=j->t->H) break;
        disparo[ny][nx] =1;
        if (j->t->celdas[ny][nx] != NULL){
            Pieza *p =(Pieza*) j->t->celdas[ny][nx];
            if(p->tipo != 'R'){
                impacto_x = nx;
                impacto_y = ny;
                p->hp -= 2;
                printf("Impacto a %c en (%d,%d) HP:%d\n", p->tipo, nx, ny, p->hp);
                if(p->hp <=0){
                    free(p);
                    j->t->celdas[ny][nx] = NULL;
                    j->turno_enemigos--;
                    printf("Enemigo eliminado\n");
                }
            }
            break;
        }
    }
    if(impacto_x != -1){
        for(int i=1; i<=3; i++){
            int bx = impacto_x + dir_x *i;
            int by = impacto_y + dir_y *i;
            if(bx<0 || bx>=j->t->W || by<0 || by>=j->t->H) break;
            disparo[by][bx] =1;
            if(j->t->celdas[by][bx] !=NULL){
                Pieza *p = (Pieza*) j->t->celdas[by][bx];
                if(p->tipo != 'R'){
                    p->hp -=1;
                    printf("Impacto detras a %c en (%d,%d) HP:%d\n", p->tipo, bx, by, p->hp);
                    if(p->hp <= 0){
                        free(p);
                        j->t->celdas[by][bx] =NULL;
                        j->turno_enemigos--;
                        printf("Enemigo eliminado\n");
                    }
                }
            }
        }
    }
    tablero_con_disparo(j->t, disparo); 
    return true;
}

bool francotirador(struct Juego *j, int dir_x, int dir_y){
    int disparo[20][20] = {0};
    int x = j->jugador->x;
    int y = j->jugador->y;
    printf("Sniper disparado en direccion (%d,%d)\n", dir_x, dir_y);
    while(1){
        x +=dir_x;
        y +=dir_y;
        if(x<0 || x>=j->t->W || y<0 || y>=j->t->H) break;
        disparo[y][x] = 1;
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
    tablero_con_disparo(j->t, disparo);
    return true;
}

bool granada(struct Juego *j, int target_x, int target_y){
    int disparo[20][20] = {0};
    int gx = j->jugador->x + target_x*3;
    int gy = j->jugador->y + target_y*3;
    printf("Granada lanzada hacia (%d,%d)\n", gx, gy);
    if(gx<0 || gx>=j->t->W || gy<0 || gy>=j->t->H){
        printf("Granada fuera del tablero\n");
        return false;
    }
    for(int i=-1; i<=1; i++){
        for(int k=-1; k<=1; k++){
            int x= gx + k;
            int y= gy + i;
            if(x<0 || x>=j->t->W || y<0 || y>=j->t->H) continue;
            disparo[y][x] = 1;
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
    tablero_con_disparo(j->t, disparo);
    return true;
}
bool especial(struct Juego *j, int dir_x, int dir_y){
    int disparo[20][20] = {0};
    int x = j->jugador->x;
    int y = j->jugador->y;
    printf("Pulso Real en (%d,%d)\n", dir_x, dir_y);
    for(int i=1; i<=3; i++){
        int nx=x+ dir_x *i;
        int ny=y+dir_y *i;
        if(nx<0 || nx>=j->t->W || ny<0 || ny>=j->t->H) break;
        disparo[ny][nx] =1;
        if(j->t->celdas[ny][nx] !=NULL){
            Pieza *p = (Pieza*) j->t->celdas[ny][nx];
            if(p->tipo != 'R'){
                p->hp -= 1;
                printf("Pulso golpea a %c en (%d,%d) HP:%d\n", p->tipo, nx, ny, p->hp);
                int emp_x=nx + dir_x;
                int emp_y=ny + dir_y;
                if(emp_x>=0 && emp_x<j->t->W && emp_y>=0 && emp_y<j->t->H){
                    if(j->t->celdas[emp_y][emp_x] == NULL){
                        j->t->celdas[ny][nx] = NULL;
                        p->x =emp_x;
                        p->y =emp_y;
                        j->t->celdas[emp_y][emp_x] =p;
                    } else {
                        free(p);
                        j->t->celdas[ny][nx] =NULL;
                        j->turno_enemigos--;
                        printf("Enemigo destruido\n");
                    }
                }
                if(p->hp <= 0){
                    free(p);
                    j->t->celdas[ny][nx] = NULL;
                    j->turno_enemigos--;
                    printf("Enemigo eliminado\n");
                }
            }
        }
    }
    tablero_con_disparo(j->t, disparo);
    return true;
}
