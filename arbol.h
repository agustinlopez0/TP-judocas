#ifndef __ARBOL_H__
#define __ARBOL_H__

#include <stddef.h>

typedef struct{
    char* nombre, *apellido;
    int edad;
} _Judoca;
typedef _Judoca *Judoca;

typedef struct{
    Judoca participante1, participante2;
    int estadoPareja;
} _Pareja;
typedef _Pareja *Pareja;
 
typedef struct _TNodo{
    void *dato;
    struct _TNodo *izq, *der;
} TNodo;
typedef TNodo *Arbol;

typedef void (* Destruir ) ( void * dato );

/**
 * Toma el nombre de un archivo y un equipo 1 o 2
 * y devuelve un arbol de judocas
 */
Arbol creaABB( char *archivo, int team );

/**
 * Crea un arbol vacio y lo retorna 
 */
Arbol createTree();

/**
 * isEmpty: retorna True (1) si el árbol esta vacio y False (0) en caso contrario.
 */
int isEmpty(Arbol a);

/**
 * Crea un judoca vacio y lo retorna
 */
Judoca createJudoca();

/**
 * Toma un string y retorna un judoca
 */
Judoca stringToJudoca( char *str );

/**
 * Agrega un un dato al arbol a
 */
Arbol agrega(Arbol a, Judoca dato);

/**
 * muestra equipos
 */
void muestraPreOrder(Arbol a);

/**
 * Muestra un Judoca
 */
void muestraJudoca( Judoca judoca );

/**
 * Muestra una Pareja
 */
void muestraPareja( Pareja pa, char* archivo );

/**
 * Devuelve true si la edad del judoca a es mayor a la del judoca b
 */
int compararEdades( Judoca a, Judoca b );

/**
 * Crea las parejas de judocas con los criterios del enunciado
 */
void crea_parejas(Arbol team1, Arbol team2, char* archivo);

/**
 * Compara un judoca y devuelve true si son iguales
 */
int compararJudoca(Judoca a, Judoca b);

/**
 * Elimina un judoca dentro de un arbol
 */
Arbol eliminaNodo(Arbol a, Judoca dato);


/**
 * Recibe un judoca y le busca una pareja en el arbol
 */
Pareja buscarPareja(Judoca judoca1, Arbol team2, char* archivo);

/**
 * Toma 2 judocas y devuelve una pareja
 */
Pareja formarPareja(Judoca judoca1, Judoca judoca2, int a);


Arbol buscaMayorDeMenores(Arbol a);

#endif