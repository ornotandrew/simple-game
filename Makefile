CC = g++
CFLAGS = -Wall -std=c++11 -D_REENTRANT
INCLUDES = -I/usr/local/include/SDL2
LFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL2 -lpthread

SRC = $(wildcard *.cpp)
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
	rm -f $(TARGET) $(OBJ)
