# Teoria dos Grafos 2019-1 - Trabalho Pratico
# Hadamo da Silva Egito
# Maiana Rodrigues Gonçalves

CC= gcc
CFLAGS= -O3
DEPS= grafo.h
OBJ= sudoku.o grafo.o
EXEC= sudoku
RM= rm -f


all: $(EXEC) $(DEPS)


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

sudoku: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(EXEC) $(OBJ)
