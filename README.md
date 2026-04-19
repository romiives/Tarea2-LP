Alumno = Romina Valdés
Rol = 202473517-9

## Sobre el código
Creación de Arma especial: "Pulso Real"
- al momento de utilizarla, el rey emite un pulso en una dirreción elegida que avanza hasta 3 casillas, inflinge daño a los enemigos en su trayectoria y empuja a los enemigos a una casilla en la dirección del disparo.
- si la casilla siguiente está libre, se empuja. Si esta ocupada o fuera del tablero el enemigo es eliminado.
- esta arma permite controlar la posicion de los enemigos y eliminar multiples emenigos

## Ciclo del juego
1. El jugador ingresa una acción, ya sea movimiento (Q,W,E,A,D,Z,S,C) o disparo (1-4).
2. La acción es ejcutada
4. Dependiendo de la acción se actualiza el estado de enemigos restante o el rey avanza por el tablero y los enmigos se mueven hacia el rey.
6. Se verifica condicón de derrota o victoria.

-> la derrota significa la muerte del rey.
-> para salir del juego hay que ingresar la letra x, si el rey muere el juego se termina automaticamente y para volver a inicializarlo se debe de ejecutar ./juego

## Sobre la compilacion
el juego fue compilado y ejecutado con el siguiente comando:
gcc -Wall -Wextra -Werror main.c tablero.c piezas.c armas.c -o juego
./juego
- tambien se puede ejcutar con make y luego ./juego
