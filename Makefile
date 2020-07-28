CC = g++
CFLAGS = -std=c++17 -Wpedantic

all:
	$(CC) $(CFLAGS) gol.cpp -o gol -lsfml-graphics -lsfml-window -lsfml-system && ./gol 40 10
