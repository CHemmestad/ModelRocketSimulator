CC = gcc

all: test

test: EulersMethod.o EulersMethodFunctions.o Forces.o
	$(CC) EulersMethod.o EulersMethodFunctions.o Forces.o -o test

EulersMethod.o: EulersMethod.c
	$(CC) -c EulersMethod.c

EulersMethodFunctions.o: EulersMethodFunctions.c
	$(CC) -c EulersMethodFunctions.c

Forces.o: Forces.c
	$(CC) -c Forces.c

clean:
	rm -f *.o test