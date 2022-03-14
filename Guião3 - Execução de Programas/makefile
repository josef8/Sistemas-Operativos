CC = gcc
CFLAGS = -w -O2  


all: ex1 ex2 ex3 ex4 
	./ex1.o
	./ex2.o
	./ex3.o ls ls ls
	./ex4.o

ex1: 
	$(CC) $(CFLAGS) ex1.c -o ex1.o

ex2: 
	$(CC) $(CFLAGS) ex2.c -o ex2.o

ex3: 
	$(CC) $(CFLAGS) ex3.c -o ex3.o

ex4: 
	$(CC) $(CFLAGS) ex4.c -o ex4.o

clean:
	@ rm -rf *.o