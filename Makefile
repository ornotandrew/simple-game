CC = g++
CFLAGS = -Wall -std=c++11
INCLUDES = -I/usr/local/include/SDL2 -Iinclude
LFLAGS = -L/usr/local/lib -lSDL2

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = simple-game

default: main

main: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

run: clean main
	./$(TARGET)

clean:
	rm -f src/*.o
