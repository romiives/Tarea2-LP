#include <stdio.h>
#include "armas.h"

bool_escopeta(struct Juego *j, int dx, int dy){
    printf("Disparo escopeta(%d,%d)\n", dx, dy);
    return true;
}
bool_francotirador(struct Juego *j, int dx, int dy){
    printf("Disparo sniper\n");
    return true;
}
bool_granada(struct Juego *j, int x, int y){
    printf("Granada lanzada\n");
    return true;
}
bool_especial(struct Juego *j, int dx, int dy){
    printf("Arma Especial\n");
    return true;
}
