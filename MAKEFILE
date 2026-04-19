#Compilar
CC = gcc
#Flags
CFLAGS = -Wall -Wextra -Werror
#Archivos
SRC = main.c tablero.c piezas.c armas.c
OBJ = $(SRC:.c=.o)
#Ejecucion
TARGET = juego
#REGLA
all: $(TARGET)
#Compilacion
$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
%.o: %.c
    $(CC) $(CFLAGS) -C $< -O $@

#JUEGO
run: $(TARGET)
    ./$(TARGET)

#Limpiar
clean:
    rm -f $(OBJ) $(TARGET)