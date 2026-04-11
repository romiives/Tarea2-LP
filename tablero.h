typedef struct {
    int W, H;
    void ***celdas; /* celdas[y][x] apunta a Celda* */
} Tablero;
struct Tablero* tablero_crear(int ancho, int alto);
void tablero_imprimir(struct Juego *juego);
void tablero_liberar(struct Tablero *tablero); /* debe limpiar la memoria heap */