CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c tablero.c piezas.c armas.c
OBJ = $(SRC:.c=.o)

TARGET = juego

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)