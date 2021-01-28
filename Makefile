CC = g++
CFLAGS = -std=c++17 -Wpedantic -g

all:
	$(CC) $(CFLAGS) main.cpp gol.cpp -o gol -lsfml-graphics -lsfml-window -lsfml-system && ./gol 40 10

clean:
	$(RM) gol
