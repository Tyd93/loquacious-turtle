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
		return 0;
	}
	return 1;
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
* Funcion que creara un archivo diferente
* cada vez que sea llamada, para representar
* cada paso que da graphviz.
*/

int imprimeDijkstra(grafo *g, int nroArchivo){
	char *nombre = (char *)malloc(2 *sizeof(int)); //Pido memoria para almacenar un INT como STRING.
	sprintf(nombre,"%i.dot",nroArchivo);
	//Almaceno el Int en la cadena.
	FILE *archivo = fopen(nombre,"w");			//El archivo lleva el nombre de INT.
	//Empiezo con las caracteristicas del grafo.
	fprintf(archivo, "digraph avance%i {\n",nroArchivo);
	fprintf(archivo, "\trankdir=LR;\n");
	fprintf(archivo, "\tnode [style = filled, fillcolor = white, fontcolor = black];\n");
	fprintf(archivo, "\tedge [color = black];\n");
	for(int i = 0;i < g->nVertices; i++){
	//Empezare a imprimir
		nodo *auxNodo = g->arreglo[i].vecino;
		while(auxNodo != NULL){
			int referencia = auxNodo->numNodo;
			fprintf(archivo, "\t%s->%s [label = %i];\n",g->arreglo[i].info,g->arreglo[referencia].info, auxNodo->peso);
			fprintf(archivo, "%s [label = %i];\n",g->arreglo[i].info,g->arreglo[i].pesoTotal);
			fprintf(archivo, "%s [label = %i];\n",g->arreglo[referencia].info,g->arreglo[referencia].pesoTotal);
			auxNodo = auxNodo->sig;
		}
	}
	fprintf(archivo, "};\n");
	fclose(archivo);
	return nroArchivo + 1;	//Leer mas abajo.
}

/*
* C es tan podereso...
* Pero si retornamos el incremento de un INT (i++)
* simplemente, no pasa nada.
*/

/*
* Funcion que representa el algoritmo
* de Dijkstra para encontrar la ruta de
* menor peso que recorra todos los nodos.
*/

int dijkstra(grafo *g, int origen){
	int u = 0;	//Auxiliar.
	grafo *auxGrafo = g;
	int nroArchivo = 0;	//Servira para enumerar archivos.
	int salir = 0;
	//Creamos la cola de prioridades.
	colaPrioridad *cp = crearCola();
	//Agregamos el origen a la cola de prioridad.
	llegada(cp,origen,auxGrafo->arreglo[origen].pesoTotal);
	auxGrafo->arreglo[origen].pesoTotal = 0; //Peso del origen
	nroArchivo = imprimeDijkstra(auxGrafo,nroArchivo);
	salir = esVaciaCola(cp);
	while(salir != 1){
		u = atencion(cp);
		while(!fueVisitado(auxGrafo,u)){
		/*
		* Mientras no encontremos un nodo que
		* no haya sido visitado, seguiremos
		* sacando elementos de la cola.
		*/
			u = atencion(cp);
		}
		auxGrafo->arreglo[u].color = 0;
		//Marcamos el vertice como "visitado".
		while(auxGrafo->arreglo[u].vecino != NULL){
		//Mientras haya vertices adyacentes a este.
			int w = retornaPeso(auxGrafo,u); //Guardamos el peso.
			if(fueVisitado(auxGrafo, auxGrafo->arreglo[u].vecino->numNodo)){
			//Si no ha sido visitado, procedemos a hacer la relajacion.
			/*
			* Nota personal: creo que el metodo de impresion en archivo
			* deberia estar implementado en esta parte para ir documentando
			* el paso a paso.
			*/
				relajacion(cp,auxGrafo,u,auxGrafo->arreglo[u].vecino->numNodo,w);
				nroArchivo = imprimeDijkstra(auxGrafo,nroArchivo);
			}
			auxGrafo->arreglo[u].vecino = auxGrafo->arreglo[u].vecino->sig;
		}
		salir=esVaciaCola(cp);
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