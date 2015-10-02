/*
* Libreria de grafo para desarrollar
* el algoritmo de Dijkstra en
* C.
* Creado por Sebastian Urrutia 15/09/15
* http://github.com/tyd93
*/

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef NODO_H
#include "nodo.h"
#define NODO_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef LIMITS_H
#include <limits.h>
#define LIMITS_H
#endif

/*
* Estructura que representa
* el grafo que sera no dirigido,
* lo cual es lo conveniente en 
* la solucion.
*/

 typedef struct eGrafo{
 	unsigned int nVertices;	//Numero de vertices del grafo.
 	unsigned int nAristas;	//Numero de aristas del grafo.
 	vertice *arreglo;		//Arreglo de vertices del grafo.
 }grafo;

/*
* Funcion que cargara un grafo con
* informacion de cada vertice y el
* color inicial.
*/

int cargarGrafo(grafo *g){
	if(g->nVertices == 0){
		printf("Error al cargar Grafo\n");
		return 0;
	}
	else{
		int largo = 0; //Variable que nos permitira guardar el largo de un String.
		//Empezamos a asignar nombres.
		largo = strlen("Chigualoco") + 1;
		char *p = (char *)malloc(largo *sizeof(char));
		p = "Chigualoco";
		g->arreglo[0].info = p;
		//
		largo = strlen("Salsipuedes") + 1;
		char *p1 = (char *)malloc(largo *sizeof(char));
		p1 = "Salsipuedes";
		g->arreglo[1].info = p1;
		//
		largo = strlen("Peor_es_nada") + 1;
		char *p2 = (char *)malloc(largo *sizeof(char));
		p2 = "Peor_es_nada";
		g->arreglo[2].info = p2;
		//
		largo = strlen("Roma") + 1;
		char *p3 = (char *)malloc(largo *sizeof(char));
		p3 = "Roma";
		g->arreglo[3].info = p3;
		//
		largo = strlen("Entrepiernas") + 1;
		char *p4 = (char *)malloc(largo *sizeof(char));
		p4 = "Entrepiernas";
		g->arreglo[4].info = p4;
		//
		largo = strlen("La_Calor") + 1;
		char *p5 = (char *)malloc(largo *sizeof(char));
		p5 = "La_Calor";
		g->arreglo[5].info = p5;
		//
		largo = strlen("Las_Coimas") + 1;
		char *p6 = (char *)malloc(largo *sizeof(char));
		p6 = "Las_Coimas";
		g->arreglo[6].info = p6;
		//
		largo = strlen("Carino_Botado") + 1;
		char *p7 = (char *)malloc(largo *sizeof(char));
		p7 = "Carino_Botado";
		g->arreglo[7].info = p7;
		//Fin de la asignacion de info. Comienza la asignacion de color.
		for(int i = 0; i < g->nVertices; i++){
			g->arreglo[i].color = 1; 			//Asignamos los nodos como no visitados.
			g->arreglo[i].padre = -1; 			//Padre NULO hasta el momento.
			g->arreglo[i].pesoTotal = INT_MAX;	//Peso Total INFINITO.
		}
		return 1;
	}
}

/*
* Funcion encargada de inicializar
* un grafo, la cual necesita un numero
* de vertices para dicho grafo.
*/

 grafo *crearGrafo(int verti){
 	grafo *auxGrafo;
 	auxGrafo = (grafo *)malloc(sizeof(grafo));
 	auxGrafo->nVertices = verti;
 	auxGrafo->nAristas = 0; //Hasta el momento, no hay ninguna arista.
 	auxGrafo->arreglo = (vertice *)malloc(verti *sizeof(vertice));
 	for(int i = 0;i < verti; i++){
 		auxGrafo->arreglo[i].vecino = NULL;	//Dejaremos como NULL los punteros hacia los vecinos.
 	}
 	return auxGrafo;
 }

 /*
 * Funcion que nos agregara una 
 * conexion dirigida entre un vertice
 * y un nodo de referencia a otro
 * vertice.
 * El nuevo nodo SIEMPRE sera agregado
 * al principio de la lista.
 */

 int agregaConexion(grafo *g, int origen, int destino, unsigned int distancia){
 	if(g->nVertices == 0){
 		printf("No se puede agregar conexion.\n\n");
 		return 0;
 	}
 	else{
 		nodo *auxNodo = crearNodo(destino,distancia);	//Nuestro nuevo nodo ha sido creado.
 		auxNodo->sig = g->arreglo[origen].vecino; 		//Apuntamos al inicio de la lista de adyacencia.
 		g->arreglo[origen].vecino = auxNodo;			//El nuevo nodo es el nuevo inicio.
 		g->nAristas++;
 		printf("Conexion agregada exitosamente.\n\n");
 		return 1;
 	}
 }

 /*
 * Funcion practica que nos permitira
 * imprimir el grafo en su totalidad.
 * Retorna cero si el grafo esta vacio.
 */

 int imprimirGrafo(grafo *g){
 	if(g->nVertices == 0){
 		printf("No es posible imprimir.\n");
 		return 0;
 	}
 	else{
 		for(int i = 0; i < g->nVertices; i++){	//Ciclo necesario para recorrer el arreglo de vectores.
 			nodo *auxPrint = g->arreglo[i].vecino;
 			printf("Ciudades alcanzables desde %s: \n",g->arreglo[i].info);
 			while(auxPrint != NULL){	//Nos saldremos cuando ya no hayan más nodos.
 				printf("\t%s, a una distancia de %i Kms.\n",g->arreglo[auxPrint->numNodo].info, auxPrint->peso);
 				auxPrint = auxPrint->sig;	//Avanzamos en la lista de nodos adyacentes.
 			}
 			printf("\n");
 		}
 		printf("Impresion exitosa.\n");
 		return 1;
 	}
 }