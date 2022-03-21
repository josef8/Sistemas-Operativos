CC = gcc
CFLAGS = -w -O2  

all: ex1.o ex2.o ex3.o ex4.o
	mv ./ex1.o ./objs
	mv ./ex2.o ./objs
	mv ./ex3.o ./objs
	mv ./ex4.o ./objs
	./objs/ex1.o
	./objs/ex2.o
	./objs/ex3.o
	./objs/ex4.o -o ./saida/saida4.txt wc saida/saida2.txt

ex1.o: ex1.c
	$(CC) $(CFLAGS) ex1.c -o ex1.o

ex2.o: ex2.c
	$(CC) $(CFLAGS) ex2.c -o ex2.o

ex3.o: ex3.c
	$(CC) $(CFLAGS) ex3.c -o ex3.o

ex4.o: ex4.c
	$(CC) $(CFLAGS) ex4.c -o ex4.o


clean:
	@ rm -rf ./objs/*.o
	@ rm -rf ./saida/*.txt
	@ rm -rf ./erros/*.txt