/*
* Libreria nodo para 
* representar los elementos de un grafo
* para representar el algoritmo
* de Dijkstra.
* Creado por Sebastian Urrutia 15/09/15
* http://github.com/tyd93
*/

#ifndef LIMITS_H
#include <limits.h>
#define LIMITS_H
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

/*
* Estructura de un nodo,
* la cual representara un
* elemento de la lista de 
* adyacencia de un vertice.
*/ 

typedef struct eNodo{
	int numNodo;		//Referencia al vertice.
	unsigned int peso;	//Referencia al peso entre vertices adyacentes. Siempre positivo.
	struct eNodo *sig;	//Puntero hacia el siguiente adyacente.	
}nodo;

/*
* Esta estructura representa un 
* vertice, el cual es una estructura
* del grafo.
* Utilizare "String" como la informacion
* contenida por este.
*/

typedef struct eVertice{
	char *info;		//Puntero a una cadena de caracteres.
	int color;		//Usare -1, 0, 1, para representar blanco, gris y negro.
	unsigned int pesoTotal;	//Referencia a la sumatoria de peso que se le asignara en Dijkstra.
	int padre;		//Representara la ubicacion del padre.
	nodo *vecino;	//Puntero hacia el inicio de la lista de adyacencia.
}vertice;


//Funcion que retorna un puntero a nodo.
nodo *crearNodo(int destino, unsigned int distancia){
	nodo *auxNodo;
	auxNodo = (nodo *)malloc(sizeof(nodo));
	auxNodo->numNodo = destino; //Le asignamos la referencia de vertice al nodo.
	auxNodo->peso = distancia;
	auxNodo->sig = NULL;
	return auxNodo;
}

