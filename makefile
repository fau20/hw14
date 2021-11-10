all: signal.o
	gcc -o program signal.o

signal.o: signal.c
	gcc -c signal.c

run:
	./program
