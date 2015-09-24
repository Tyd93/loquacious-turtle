/*
* Libreria para definir la
* estructura y operaciones 
* de una cola de prioridad
* para el algoritmo de 
* Dijkstra.
* Creado por Sebastian Urrutia 21/09/15
* http://github.com/tyd93
*/

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef NODO_H
#include "nodo.h"
#define NODO_H
#endif

#ifndef GRAFO_H
#include "grafo.h"
#define GRAFO_H
#endif

/*
* Estructura del nodo que almacenara
* la cola de prioridades.
* Basicamente contiene dos variables
* "INT" que indican el nodo y la distancia
* acumulada hacia el nodo.
*/

typedef struct eNodoCola{
	int referenciaVertice;
	int referenciaPesoVertice;
	struct eNodoCola *sig;
}nodoCola;


/*
* Estructura que representa
* una Cola.
* Las operaciones sobre esta
* la haran una Cola de 
* Prioridad.
*/

typedef struct eColaPrioridad{
	int largo;
	nodoCola *frente;
	nodoCola *ventana;
	nodoCola *final;
}colaPrioridad;

/*
* Funcion que retornara un puntero
* a una cola de prioridad vacia.
*/

colaPrioridad *crearCola(){
	colaPrioridad *auxCola = (colaPrioridad *)malloc(sizeof(colaPrioridad));
	auxCola->frente = NULL;
	auxCola->largo = 0;
	auxCola->ventana = NULL;
	auxCola->final = NULL;
}

/*
* Funcion auxiliar para saber
* si la cola de prioridad 
* contiene algun elemento.
*/

int esVaciaCola(colaPrioridad *cp){
	if(cp->largo == 0){
		return 1;
	}
	return 0;
}

/*
* Funcion que nos permitira ubicar
* un puntero ventana para realizar
* una operacion de insercion en 
* orden dentro de la cola de 
* prioridad.
* Es importante enviar o igualar a 
* el puntero "colaPrioridad->ventana".
*/

nodo *ubicarVentana(nodo *ventana, int prio){

}

/*
* Funcion que devuelve un nodo de mayor prioridad
* (en nuestro caso, el de menor peso) desde la 
* cola de prioridad.
*/

int atencion(colaPrioridad *cp){
	if(esVaciaCola(cp)){
		printf("La cola esta vacia.\n");
		return 1;
	}
	else{
		nodoCola *auxNodocola;
		auxNodocola = cp->frente;
		if(cp->largo == 1){
		//Si solo queda un elemento.
			cp->frente = NULL;
			cp->final = cp->frente;
			cp->largo--;
			return auxNodocola->referenciaVertice;
		}
		cp->frente = cp->frente->sig;
		cp->largo--;
		return auxNodocola->referenciaVertice;
	}
}

/*
* Funcion que agregara ordenadamente
* la referencia a un vertice para
* luego utilizarlo en el algoritmo
* de Dijkstra.
* Se ordenara segun "pesoDestino", que
* corresponde al peso de la distancia
* total desde un nodo origen hacia 
* un nodo destino del grafo.
*/

int llegada(int destino, int pesoDestino){
	if(){
		
	}
	return 1;
}