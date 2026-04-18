#include <stdio.h>
#include "armas.h"

bool escopeta(struct Juego *j, int dx, int dy){
    (void)j;
    (void)dx;
    (void)dy;
    printf("Disparo escopeta(%d,%d)\n", dx, dy);
    return true;
}
bool francotirador(struct Juego *j, int dx, int dy){
    (void)j;
    (void)dx;
    (void)dy;
    printf("Disparo sniper\n");
    return true;
}
bool granada(struct Juego *j, int x, int y){
    (void)j;
    (void)x;
    (void)y;
    printf("Granada lanzada\n");
    return true;
}
bool especial(struct Juego *j, int dx, int dy){
    printf("Arma Especial\n");
    (void)j;
    (void)dx;
    (void)dy;
    return true;
}
