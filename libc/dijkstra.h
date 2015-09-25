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

#ifndef NODO_H
#include "nodo.h"
#define NODO_H
#endif

/*
* Funcion de utilidad que nos permitira saber 
* si un nodo ha sido visitado.
* Retorna "1" en caso de ser cierto.
*/

int fueVisitado(grafo *g, int origen){
	if(g->arreglo[origen].color == 0){
		printf("El nodo ya ha sido visitado.\n");
		return 1;
	}
	return 0;
}

/*
* Funcion que retornara el peso 
* (distancia entre nodos adyacentes)
* de un nodo origen a uno destino
*/

int retornaPeso(grafo *g, int origen){
	/*
	* Es muy simple ya que devuelve el peso del primer nodo,
	* y a medida que le damos a siguiente, siempre va a ser
	* diferente.
	*/
	return g->arreglo[origen].vecino->peso;
}

/* Antigua funcion.
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
*/

/*
* Funcion que realiza una comparacion
* entre la distancia total hacia un
* vertice adyacente y la distancia actual.
*/

int relajacion(colaPrioridad *cp, grafo *g, int actual, int adyacente, int peso){
	if(g->arreglo[actual].pesoTotal + peso < g->arreglo[adyacente].pesoTotal){
	//Pregunto si la distancia que llevo hasta ahora, es menor que la distancia del origen hacia el destino.
		g->arreglo[adyacente].pesoTotal = g->arreglo[actual].pesoTotal + peso;
		llegada(cp,adyacente,g->arreglo[adyacente].pesoTotal);
		return 1;
	}
	return 0;
}

/*
* Funcion que representa el algoritmo
* de Dijkstra para encontrar la ruta de
* menor peso que recorra todos los nodos.
*/

int dijkstra(grafo *g, int origen){
	int u = 0;	//Auxiliar.
	//Creamos la cola de prioridades.
	colaPrioridad *cp = crearCola();
	//Agregamos el origen a la cola de prioridad.
	llegada(cp,origen,g->arreglo[origen].pesoTotal);
	while(!esVaciaCola(cp)){
		u = atencion(cp);
		while(!fueVisitado(g,u)){
		/*
		* Mientras no encontremos un nodo que
		* no haya sido visitado, seguiremos
		* sacando elementos de la cola.
		*/
			u = atencion(cp);
		}
		g->arreglo[u].color = 0;
		//Marcamos el vertice como "visitado".
		while(g->arreglo[u].vecino != NULL){
		//Mientras haya vertices adyacentes a este.
			int w = retornaPeso(g,u); //Guardamos el peso.
			if(fueVisitado(g, g->arreglo[u].vecino->numNodo)){
			//Si no ha sido visitado, procedemos a hacer la relajacion.
			/*
			* Nota personal: creo que el metodo de impresion en archivo
			* deberia estar implementado en esta parte para ir documentando
			* el paso a paso.
			*/
				relajacion(cp,g,u,g->arreglo[u].vecino->numNodo,w);
			}
			g->arreglo[u].vecino = g->arreglo[u].vecino->sig;
		}
	}
	return 1;
}

/*
* Dejare como comentario mi antigua funcion
* "retornaPeso" para marcar un precedente.
* Basicamente implementarla era mas facil de
* lo que yo creia.
* 24/09/15 23:06
*/

/*
* Creo que hare una funcion "retornaVertice"
* que reciba como parametro el grafo y el origen,
* para retornar el numero del nodo adyacente y asi evitar 
* escribir cosas como "g->arreglo[u].vecino->numNodo"
* 24/09/15 23:36
*/