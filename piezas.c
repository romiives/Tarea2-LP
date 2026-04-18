#include <stdlib.h>
#include <time.h>
#include "piezas.h"
#include <stdio.h>
#include "main.h"
#include <math.h>

Pieza* crear_en_fila(Tablero *t, char tipo, int hp, int fila){
    Pieza *p = malloc(sizeof(Pieza));
    p->tipo = tipo;
    p->hp = hp;
    int x;
    do{
        x = rand() % t->W;
    }while(t->celdas[fila][x] != NULL);
    p->x = x;
    p->y = fila;
    t->celdas[fila][x] = (void*) p;
    return p;
}

//creacion del rey en la ultima fila
Pieza* crear_rey(Tablero *t){
    Pieza *rey = malloc(sizeof(Pieza));
    rey->tipo = 'R';
    rey->hp = 10;
    int x;
    do{
        x = rand() % (t->W-2)+1;
    }while(t->celdas[t->H-1][x]!= NULL);
    rey->x = x;
    rey->y = t->H - 1;
    t->celdas[rey->y][rey->x] = rey;
    return rey;
}

Pieza* crear_peon(Tablero *t){return crear_en_fila(t,'P',1,1);}
Pieza* crear_caballo(Tablero *t){return crear_en_fila(t,'C',2,0);}
Pieza* crear_alfil(Tablero *t){return crear_en_fila(t,'A',2,0);}
Pieza* crear_torre(Tablero *t){return crear_en_fila(t,'T',4,0);}
Pieza* crear_reina(Tablero *t){return crear_en_fila(t,'Q',3,0);}


void spawn_nivel(struct Juego *j, int nivel){
    if(nivel == 1){
        for(int i=0;i<4;i++) crear_peon(j->t);
        for(int i=0;i<2;i++) crear_caballo(j->t);
        for(int i=0;i<2;i++)crear_alfil(j->t);
        j->turno_enemigos = 8;
    }
    else if(nivel == 2){
        for(int i=0;i<4;i++) crear_peon(j->t);
        for(int i=0;i<2;i++) crear_caballo(j->t);
        for(int i=0;i<2;i++)crear_alfil(j->t);
        j->turno_enemigos = 8;
    }
    else if(nivel == 3){
        for(int i=0;i<2;i++) crear_peon(j->t);
        crear_reina(j->t);
        crear_alfil(j->t);
        crear_torre(j->t);
        j->turno_enemigos = 5;
    }
}
//movimiento del peon hacia el rey
void mover_peon(Tablero *t, Pieza *peon, Pieza *rey){
    int dx=0, dy=0;
    if(rey->x > peon->x) dx =1;
    else if(rey->x < peon->x) dx =-1;
    if(rey->y > peon->y) dy =1;
    else if(rey->y < peon->y) dy =-1;
    int nx = peon->x +dx;
    int ny = peon->y +dy;
    if(nx <0 || nx>= t->W || ny <0 || ny>= t->H)return;
    if(t->celdas[ny][nx] == NULL || (nx == rey->x && ny == rey->y)){
        t->celdas[peon->y][peon->x] = NULL;
        peon->x = nx;
        peon->y = ny;
        t->celdas[ny][nx] = (void*) peon;
    }
}

void mover_caballo(Tablero *t, Pieza *p, Pieza *rey){
    int movimiento[8][2] ={
        {2,1},{2,-1},{-2,1},{-2,-1},
        {1,2},{1,-2},{-1,2},{-1,-2}
    };
    int mejor_x = p->x;
    int mejor_y = p->y;
    int mejor_dist = 9999;
    for(int i=0;i<8;i++){
        int nx= p->x + movimiento[i][0];
        int ny= p->y + movimiento[i][1];
        if(nx<0||nx>=t->W||ny<0||ny>=t->H) continue;
        if(t->celdas[ny][nx] != NULL && !(nx==rey->x && ny==rey->y)) continue;
        int distancia = abs(nx - rey->x) + abs(ny - rey->y);
        if(distancia < mejor_dist){
            mejor_dist = distancia;
            mejor_x = nx;
            mejor_y = ny;
        }
    }
    t->celdas[p->y][p->x] = NULL;
    p->x = mejor_x;
    p->y = mejor_y;
    t->celdas[p->y][p->x] = (void*) p;
}

void mover_alfil(Tablero *t, Pieza *p, Pieza *rey){
    int dx = (rey->x > p->x) ? 1: -1;
    int dy = (rey->y > p->y) ? 1: -1;
    int nx = p->x + dx;
    int ny = p->y + dy;
    if(nx<0||nx>=t->W||ny<0||ny>=t->H) return;
    if(t->celdas[ny][nx] == NULL || (nx==rey->x && ny==rey->y)){
        t->celdas[p->y][p->x] = NULL;
        p->x = nx;
        p->y = ny;
        t->celdas[ny][nx] = (void*) p;
    }
}

void mover_torre(Tablero *t, Pieza *p, Pieza *rey, int turno){
    if(turno % 2 != 0) return;
    int dx =0, dy =0;
    if(abs(rey->x - p->x) > abs(rey->y - p->y)){
        dx =(rey->x > p->x) ? 1: -1;
    } else {
        dy =(rey->y > p->y) ? 1: -1;
    }
    int nx = p->x + dx;
    int ny = p->y + dy;
    if(nx<0||nx>=t->W||ny<0||ny>=t->H) return;
    if(t->celdas[ny][nx] == NULL || (nx==rey->x && ny==rey->y)){
        t->celdas[p->y][p->x] = NULL;
        p->x =nx;
        p->y =ny;
        t->celdas[ny][nx] = (void*) p;
    }
}

void mover_reina(Tablero *t, Pieza *p, Pieza *rey){
    int dx = 0, dy = 0;
    if(abs(rey->x - p->x) > abs(rey->y - p->y)){
        dx =(rey->x > p->x) ? 1: -1;
    } else {
        dy =(rey->y > p->y) ? 1: -1;
    }
    if(rey->x != p->x && rey->y != p->y){
        dx =(rey->x > p->x) ? 1: -1;
        dy =(rey->y > p->y) ? 1: -1;
    }
    int nx = p->x + dx;
    int ny = p->y + dy;
    if(nx<0||nx>=t->W||ny<0||ny>=t->H) return;
    if(t->celdas[ny][nx] == NULL || (nx==rey->x && ny==rey->y)){
        t->celdas[p->y][p->x] = NULL;
        p->x =nx;
        p->y =ny;
        t->celdas[ny][nx] = (void*) p;
    }
}

void mover_enemigos(struct Juego *j){
    for(int y=0; y<j->t->H; y++){
        for(int x=0; x<j->t->W; x++){
            if(j->t->celdas[y][x] == NULL) continue;
            Pieza *p = (Pieza*) j->t->celdas[y][x];
            if(p->tipo == 'R') continue;
            if(p->tipo == 'P') mover_peon(j->t, p, j->jugador);
            if(p->tipo == 'C') mover_caballo(j->t, p, j->jugador);
            if(p->tipo == 'A') mover_alfil(j->t, p, j->jugador);
            if(p->tipo == 'T') mover_torre(j->t, p, j->jugador, j->turno_enemigos);
            if(p->tipo == 'Q') mover_reina(j->t, p, j->jugador);
        }
    }
    j->turno_enemigos++;
}

bool verificar_estado_rey(struct Juego *j){
    for(int y=0; y<j->t->H; y++){
        for(int x=0; x<j->t->W; x++){
            if(j->t->celdas[y][x] == NULL) continue;
            Pieza *p = (Pieza*) j->t->celdas[y][x];
            if(p->tipo == 'R') continue;
            if(p->x == j->jugador->x && p->y == j->jugador->y){
                return true;
            }
        }
    }
    return false;
}