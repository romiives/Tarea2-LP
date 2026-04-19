#include <stdio.h>
#include <stdlib.h>
#include "armas.h"
#include "main.h"
#include "tablero.h"

/*
**
Parametro 1: Juego
Parametro 2: int
Parametro 3: int
***
Tipo de Retorno: bool
***
Disparo en cono: 2 de daño al primer enemigo y 1 a los que están detrás.
*/
bool escopeta(struct Juego *j, int dir_x, int dir_y){
    int disparo[j->t->H][j->t->W];
    for(int i=0;i<j->t->H;i++)
        for(int k=0;k<j->t->W;k++)
            disparo[i][k]=0;
    int x = j->jugador->x;
    int y = j->jugador->y;
    printf("Escopeta (cono) en direccion (%d,%d)\n", dir_x, dir_y);
    for(int d = 1; d <= 3; d++){
        for(int desplazaminento = -d+1; desplazaminento <= d-1; desplazaminento++){
            int nx, ny;
            if(dir_x == 0){
                nx = x + desplazaminento;
                ny = y + dir_y * d;
            }
            else if(dir_y == 0){
                nx = x + dir_x * d;
                ny = y + desplazaminento;
            }
            else{
                nx =x + dir_x * d + desplazaminento;
                ny =y + dir_y * d + desplazaminento;
            }
            if(nx<0 || nx>=j->t->W || ny<0 || ny>=j->t->H) continue;
            disparo[ny][nx] = 1;
            if(j->t->celdas[ny][nx] != NULL){
                Pieza *p = (Pieza*) j->t->celdas[ny][nx];
                if(p->tipo != 'R'){
                    p->hp -= 2;
                    printf("Impacto a %c en (%d,%d) | HP restante: %d\n",
                           p->tipo, nx, ny, p->hp);
                    if(p->hp <= 0){
                        free(p);
                        j->t->celdas[ny][nx] = NULL;
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

/*
**
Parametro 1: Juego
Parametro 2: int
Parametro 3: int
***
Tipo de Retorno: bool
***
Disparo en linea infinita. Inflinge 3 de daño al primer enemigo.
*/
bool francotirador(struct Juego *j, int dir_x, int dir_y){
    int disparo[j->t->H][j->t->W];
    for(int i=0;i<j->t->H;i++)
        for(int k=0;k<j->t->W;k++)
            disparo[i][k]=0;
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
                printf("Impacto frnacotirador a %c en (%d,%d) | HP restante:%d\n", p->tipo, x, y, p->hp);
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
/*
**
Parametro 1: Juego
Parametro 2: int
Parametro 3: int
***
Tipo de Retorno: bool
***
Explosion en un area de 3x3 a distancia 3.
*/
bool granada(struct Juego *j, int target_x, int target_y){
    int disparo[j->t->H][j->t->W];
    for(int i=0;i<j->t->H;i++)
        for(int k=0;k<j->t->W;k++)
            disparo[i][k]=0;
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
                    printf("Explosion golpea a %c en (%d,%d) | HP restante:%d\n", p->tipo, x, y, p->hp);
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

/*
**
Parametro 1: Juego
Parametro 2: int
Parametro 3: int
***
Tipo de Retorno: bool
***
Pulso que empuja enemigos o los elimina. 
*/
bool especial(struct Juego *j, int dir_x, int dir_y){
    int disparo[j->t->H][j->t->W];
    for(int i=0;i<j->t->H;i++)
        for(int k=0;k<j->t->W;k++)
            disparo[i][k]=0;
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
                printf("Pulso golpea a %c en (%d,%d) | HP restante: %d\n", p->tipo, nx, ny, p->hp);
                if(p->hp <= 0){
                    free(p);
                    j->t->celdas[ny][nx] = NULL;
                    j->turno_enemigos--;
                    printf("Enemigo eliminado\n");
                    continue; 
                }
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
            }
        }
    }
    tablero_con_disparo(j->t, disparo);
    return true;
}
