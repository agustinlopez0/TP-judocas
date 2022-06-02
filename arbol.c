#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Arbol createTree(){
    return NULL;
}

Judoca createJudoca(){
    return malloc(sizeof(Judoca));
}

Pareja createPareja(){
	return malloc(sizeof(Pareja));
}

Arbol creaABB( char *archivo, int team){
    FILE* datosEntrada;
    char buff[255];
    datosEntrada = fopen(archivo, "r");
    int bandera = 1, banderin = 2;
    Arbol arbol = createTree();

    while( (fscanf(datosEntrada,"%[^\n]%*c",buff) != EOF) && bandera ) {
    // while( (fscanf(datosEntrada,"%s",buff) != EOF) && bandera ) {
        if( team == 1 ){        // deja de leer cuando llega a equipo 2
            if( !strcmp(buff,"Equipo 2:" )){
                bandera = 0;
            }
        }

        if( team == 2 && banderin == 2){        // empieza a leer cuando llega a equipo 2
            banderin = 0;
        }
        if( !strcmp(buff,"Equipo 2:" )){
            banderin = 1;
        }
        if( strcmp(buff,"Equipo 1:") && strcmp(buff,"Equipo 2:") && banderin ){
			printf("HOLA CREA ABB antes de llamar a agrega\n");
            arbol = agrega(arbol, stringToJudoca(buff));
			printf("HOLA CREA ABB despues de llamar a agrega\n");
        }
    }

    fclose(datosEntrada);

    return arbol;
}

Judoca stringToJudoca(char persona[]){
    Judoca judoca = createJudoca();
    char delimitador[] = ",";

    char *temp = strtok(persona, delimitador);
    judoca->nombre = malloc(sizeof(char)*(strlen(temp)+1));
    strcpy(judoca->nombre,temp);
    
    temp = strtok(NULL, delimitador);
    judoca->apellido = malloc(sizeof(char)*(strlen(temp)+1));
    strcpy(judoca->apellido,temp);
    
    int tempInt = atoi(strtok(NULL, delimitador));
    judoca->edad = tempInt;
    
    return judoca;
}

Arbol agrega(Arbol a, Judoca dato){
	printf("HOLA AGREGA\n");
	if (isEmpty(a)) {
	    a = malloc(sizeof(TNodo));
	    a->dato = dato;
        // muestraJudoca(a->dato);
	    a->izq = NULL;
	    a->der = NULL;
  	}
	else {
		if (compararEdades((Judoca)a->dato, dato)){
			a->izq = agrega(a->izq, dato);
        }
		else
			a->der = agrega(a->der, dato);
	}
    // muestraPreOrder(a);
	return a;
}

void muestraPreOrder(Arbol a){
	if (!isEmpty(a)) {
        muestraJudoca(a->dato);
    	muestraPreOrder(a->izq);
    	muestraPreOrder(a->der);
  	}
}

void muestraJudoca( Judoca judoca ){
    printf("Nombre: %s - Apellido: %s - Edad: %i | \n", judoca->nombre, judoca->apellido, judoca->edad);
}


void muestraPareja( Pareja pareja, char* archivo){

    FILE* datosSalida;
    datosSalida = fopen(archivo, "a+");

	char* estado;
	switch (pareja->estadoPareja){
	case 0:
		estado = malloc(sizeof(char)*(strlen("Pareja valida") + 1));
		strcpy(estado,"Pareja valida");
		break;
	case 1:
		estado = malloc(sizeof(char)*(strlen("Uno de los judocas es mayor de edad y el otro es menor") + 1));
		strcpy(estado,"Uno de los judocas es mayor de edad y el otro es menor");
		break;
	case 2:
		estado = malloc(sizeof(char)*(strlen("Pareja de menores con diferencia mayor a 1 anio") + 1));
		strcpy(estado,"Pareja de menores con diferencia mayor a 1 anio");
		break;
	case 3:
		estado = malloc(sizeof(char)*(strlen("Pareja de mayores con diferencia mayor a 2 anios") + 1));
		strcpy(estado,"Pareja de mayores con diferencia mayor a 2 anios");
		break;
	default:
		estado = malloc(sizeof(char)*(strlen("hola juan carlos") + 1));
		strcpy(estado,"hola juan carlos");
		break;
	}

	// printf("\nEstado %i", pareja->estadoPareja);
	fprintf(datosSalida, "\n%-15s %-15s (%3i) - %-15s %-15s (%3i) - %s", 
		pareja->participante1->nombre, pareja->participante1->apellido, pareja->participante1->edad,
		pareja->participante2->nombre, pareja->participante2->apellido, pareja->participante2->edad, estado);

    fclose(datosSalida);
	free(estado);
	
}

int compararEdades( Judoca a, Judoca b ){
	return a->edad > b->edad;
}

int isEmpty(Arbol a) {
	return a == NULL;
}

Arbol eliminaNodo(Arbol a, Judoca dato) {
	if (isEmpty(a)) return NULL;
	if (!compararJudoca(a->dato, dato)) {								// compararJudoca(a->dato, dato)
		if (compararEdades(a->dato, dato))
			a->izq = eliminaNodo(a->izq, dato);
    	else
    		a->der = eliminaNodo(a->der, dato);
  	} 
  	else {
  	//Estoy en el Nodo que se desea eliminar
  		//Caso 1: No tiene hijos
  		if (isEmpty(a->izq) && isEmpty(a->der))	{
  			free(a);
  			a = NULL;
  			return a;
  		}
  		//Caso 2: Un hijo 
  		else if (isEmpty(a->izq) || isEmpty(a->der)) {
  			Arbol t = isEmpty(a->izq)? a->der : a->izq;
  			free(a);
  			a = t;
  			return a;
  		}
  		//Caso 3: 2 hijos
  		else {
  			//Encuentro el nodo que tengo que poner en su lugar, en este caso, es el mayor de los menores
  			Arbol t = buscaMayorDeMenores(a);
  			a->dato = t->dato;
  			//Borro el nodo duplicado que quedó
  			a->izq=eliminaNodo(a->izq, t->dato);
  		}
  	}
  	return a;
}

Arbol buscaMayorDeMenores(Arbol a){
	if  (a->izq == NULL) {
    	return NULL;
  	}
  	else {
	    Arbol t;
    	for(t = a->izq; t->der != NULL; t = t->der);
    	return t;
  	}
}

int compararJudoca(Judoca a, Judoca b){
	if( !strcmp(a->nombre, b->nombre) && !strcmp(a->apellido, b->apellido) && a->edad == b->edad )
		return 1;
	return 0;
}

void crea_parejas(Arbol team1, Arbol team2, char* archivo){
	if( isEmpty(team1) || isEmpty(team2) ) return ;

	Judoca judoca1 = (Judoca)team1->dato;
   
	Pareja pareja = buscarPareja(judoca1 , team2,  archivo);

	if(pareja)
		team2 = eliminaNodo(team2, pareja->participante2);

	crea_parejas(team1->izq, team2, archivo);
	crea_parejas(team1->der, team2, archivo);
crea_parejas
}

Pareja formarPareja(Judoca judoca1, Judoca judoca2, int a){
	// printf("\n%i %i\n", judoca1->edad, judoca2->edad);
	Pareja pareja = createPareja();
	pareja->participante1 = judoca1;
	pareja->participante2 = judoca2;
	pareja->estadoPareja = a;
	return pareja;
}

Pareja buscarPareja(Judoca judoca1, Arbol team2, char* archivo){

	if(isEmpty(team2)) return NULL;
	
	int edad1 = judoca1->edad;
	Judoca auxJudoca = (Judoca)team2->dato;
	int edad2 = auxJudoca->edad;

	Pareja parejaAux = createPareja();

	if ( edad1 < 18 ){
		if( edad2 >= 18 ){

			muestraPareja(formarPareja(judoca1, team2->dato, 1), archivo);
			return buscarPareja( judoca1, team2->izq, archivo );

		} else {

			if( fabs(edad1 - edad2) > 1 ){

				if( edad1 > edad2 ){

					muestraPareja(formarPareja(judoca1, team2->dato, 2), archivo);
					return buscarPareja( judoca1, team2->der, archivo );
					
				} else if( edad1 < edad2 ){

					muestraPareja(formarPareja(judoca1, team2->dato, 2), archivo);
					return buscarPareja( judoca1, team2->izq, archivo );
				}

			} else {
				parejaAux = formarPareja(judoca1, team2->dato, 0);
				muestraPareja(parejaAux, archivo);
				return parejaAux;
				
			}
		}

	} else {

		if( edad2 < 18 ){

			muestraPareja(formarPareja(judoca1, team2->dato, 1), archivo);
			return buscarPareja( judoca1, team2->der, archivo );
		}

		else{

			if( fabs(edad1 - edad2) > 2 ){
				
				if( edad1 > edad2 ){
					muestraPareja(formarPareja(judoca1, team2->dato, 3), archivo);
					return buscarPareja( judoca1, team2->der, archivo );
				
				} else if( edad1 < edad2 ){
					muestraPareja(formarPareja(judoca1, team2->dato, 3), archivo);
					return buscarPareja( judoca1, team2->izq, archivo );
				
				}

			} else{
				parejaAux = formarPareja(judoca1, team2->dato, 0);
				muestraPareja(parejaAux, archivo);
				return parejaAux;
			}
		}
	}
	return NULL;
}
