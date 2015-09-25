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
	return auxCola;
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
* Es AUN mas importante, que el nodo 
* enviado este apuntando al elemento
* que sigue del frente de la cola.
*/

nodoCola *ubicarVentana(nodoCola *ventana, int priori){
	if(ventana->sig->referenciaPesoVertice >= priori){
	/* 
	* Importante: Pregunto por el que sigue de ventana, para luego mandar ventana,
	* ya que asi me facilita la insercion, ya que la cola es simplemente enlazada.
	*/
		return ventana;
	}
	ventana = ventana->sig;
	if(ventana->sig == NULL){
		return NULL;
	}
	ubicarVentana(ventana, priori);
	return NULL;
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

int llegada(colaPrioridad *cp, int destino, int pesoDestino){
	nodoCola *auxNodocola = (nodoCola *)malloc(sizeof(nodoCola));
	auxNodocola->referenciaVertice = destino;
	auxNodocola->referenciaPesoVertice = pesoDestino;
	auxNodocola->sig = NULL;
	if(esVaciaCola(cp)){
	//1.- En el caso que no haya ningun nodo en la cola.
		cp->frente = auxNodocola;
		cp->ventana = cp->frente;
		cp->final = cp->frente;
		cp->largo++;
		return 1;
	}
	if(cp->largo == 1){
	//2.- En el caso de que solo haya un elemento en la cola.
		if(auxNodocola->referenciaPesoVertice <= cp->frente->referenciaPesoVertice){
		//2a.-Preguntamos si el frente de la cola es mayor al nuevo elemento.
			cp->frente = auxNodocola;
			cp->frente->sig = cp->final;
			cp->ventana = cp->frente;
		}
		else{
		//2b.- En el caso que no lo sea.
			cp->final = auxNodocola;
			cp->frente->sig = cp->final;
			cp->ventana = cp->frente;
		}
		cp->largo++;
		return 1;
	}
	else{
	//3.- Este es el caso mas general. Cuando hay mas de un elemento en la cola.
		if(auxNodocola->referenciaPesoVertice <= cp->frente->referenciaPesoVertice){
		//3a.- Preguntamos si nuestro nodo posee mas prioridad que el nodo en frente de la cola.
			auxNodocola->sig = cp->frente;
			cp->frente = auxNodocola;
			cp->ventana = cp->frente;
			cp->largo++;
			return 1;
		}
		else if(auxNodocola->referenciaPesoVertice > cp->frente->referenciaPesoVertice && auxNodocola->referenciaPesoVertice <= cp->frente->sig->referenciaPesoVertice){
		//3c.- Si el nodo se encuentra entre el primero y el segundo nodo. (MUY IMPORTANTE si es que hay solo dos elementos.)
			auxNodocola->sig = cp->frente->sig;
			cp->frente->sig = auxNodocola;
			cp->ventana = cp->frente;
			cp->largo++;
			return 1;
		}
		else if(auxNodocola->referenciaPesoVertice >= cp->final->referenciaPesoVertice){
		//3b.- Preguntamos si nuestro nodo posee menos prioridad que el nodo que esta en final de la cola.
			cp->final->sig = auxNodocola;
			cp->final = auxNodocola;
			cp->ventana = cp->frente;
			cp->largo++;
			return 1;
		}
		else{
		//Llegando a este punto, el nodo puede estar entre el frente y el final.
			//Ventana apuntara al elemento siguiente 
			cp->ventana = cp->frente->sig;
			ubicarVentana(cp->ventana,auxNodocola->referenciaPesoVertice);
			auxNodocola->sig = cp->ventana->sig;
			cp->ventana->sig = auxNodocola;
			cp->ventana = cp->frente;
			cp->largo++;
			return 1;
		}
	}
}