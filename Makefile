CC = g++
CFLAGS = -Wall -std=c++11 -I/usr/local/include/SDL2 -D_REENTRANT
LDFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL2 -lpthread

main: main.cpp
	$(CC) -o main main.cpp $(CFLAGS) $(LDFLAGS)

run: main
	./main

clean:
	rm -f main main.o
