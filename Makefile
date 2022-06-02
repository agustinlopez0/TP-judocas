# gcc -Wall -c arbol.c
# gcc -Wall -o main main.c arbol.o
# ./main datosEntrada.txt datosSalida.txt

all: program

program: main.c arbol.c arbol.h arbol.o
	gcc -Wall -o main main.c arbol.o

arbol.o:
	gcc -Wall -c arbol.c

clean:
	cat /dev/null > datosSalida.txt
	rm *.o main