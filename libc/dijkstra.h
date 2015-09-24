/*
* Libreria que representara
* funciones y variables para representar 
* el algoritmo de Dijkstra.
* Creado por Sebastian Urrutia 19/09/15
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

#ifndef GRAFO_H
#include "grafo.h"
#define GRAFO_H
#endif

#ifndef COLAPRIORIDAD_H
#include "colaPrioridad.h"
#define COLAPRIORIDAD_H
#endif

/*
* Funcion que retornara el peso 
* (distancia entre nodos adyacentes)
* de un nodo origen a uno destino
*/

int retornaPeso(grafo *g, int origen, int destino){
	grafo *auxGrafo = g;	//Auxiliar que nos permitira recorrer el grafo.
	while(auxGrafo->arreglo[origen].vecino != NULL){
		if(auxGrafo->arreglo[origen].vecino->numNodo == destino){
			return auxGrafo->arreglo[origen].vecino->peso;
		}
		else{
			auxGrafo->arreglo[origen].vecino = auxGrafo->arreglo[origen].vecino->sig;
		}
	}
}

/*
* Funcion que realiza una comparacion
* entre la distancia total hacia un
* vertice adyacente y la distancia actual.
*/

int relajacion(grafo *g,int actual, int adyacente, int peso){
	if(g->arreglo[actual].pesoTotal + peso < g->arreglo[adyacente].pesoTotal){	
		g->arreglo[adyacente].pesoTotal = g->arreglo[actual].pesoTotal + peso;
		grafo *auxGrafo = g;
		while(auxGrafo->arreglo[actual].vecino != NULL){
			if(auxGrafo->arreglo[actual].vecino->numNodo == adyacente){
				llegada(cp, auxGrafo->arreglo[actual].vecino);
				return 1;
			}
			auxGrafo->arreglo[actual].vecino = auxGrafo->arreglo[actual].vecino->sig;
		}
	}
}

/*
* Funcion que representa el algoritmo
* de Dijkstra para encontrar la ruta de
* menor peso que recorra todos los nodos.
*/

int dijkstra(grafo *g, nodo *nodoOrigen){

	return 1;
}