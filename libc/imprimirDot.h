/*
* Libreria para imprimir el grafo 
* en un archivo.dot
* esta libreria SOLO imprimira el grafo completo.
* La impresion en Dijkstra se hara dentro de dicha funcion,
* o podria hacerlo aca pero con un modulo diferente.
* Creado por Sebastian Urrutia el 01-10-15.
*/

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef COLAPRIORIDAD_H
#include "colaPrioridad.h"
#define COLAPRIORIDAD_H
#endif

#ifndef GRAFO_H
#include "grafo.h"
#define GRAFO_H
#endif

#ifndef NODO_H
#include "nodo.h"
#define NODO_H
#endif

/*
* Funcion que imprimira todo el grafo 
* en un archivo ".dot" para reproducirlo
* con el SoftWare Graphviz.
* Funcion creada por el profe  Mauro San Martin.
*/

int imprimeGrafoDotProfe(grafo *g){
	if(g->nVertices == 0){
		printf("No es posible imprimir");
		return 0;
	}
	else{
		FILE *archivoDot;
		archivoDot = fopen("grafoViz.dot","w");
		/*
		* Creamos el archivo y luego le damos atributos al grafo.
		* Como por ejemplo color del nodo representado y ademas
		* color de la arista, etc.
		*/
		fprintf(archivoDot, "digraph grafo{\n");
		fprintf(archivoDot, "\tsplines = true;\n");
		fprintf(archivoDot, "\tnode [style = filled, fillcolor = white, fontcolor = black];\n");
		fprintf(archivoDot, "\tedge [color = black];\n");
		for(int i = 0; i < g->nVertices; i++){
			if(i % 2 == 0){
				fprintf(archivoDot, "\t %i [label = \"%s\"];\n",i,g->arreglo[i].info);
			}
			else{
				fprintf(archivoDot, "\t %i [label = \"%s\", fontcolor = white, fillcolor = gray];\n",i,g->arreglo[i].info);
			}
			/*
			* Una vez hecho el vertice, dibujaremos las adyacencias.
			* Para ello crearemos un auxiliar de tipo nodo que
			* apuntara al primer vecino como primera instancia,
			* para luego pasar al siguiente y todo esto hasta que
			* nuestro auxliar llegue al fin de la lista de adyacencia.
			*/
			nodo *auxNodo = g->arreglo[i].vecino;
			while(auxNodo != NULL){
				if(i == 2){
					fprintf(archivoDot, "\t%i->%i [label = \"%i\", color = blue, penwidth = 2];\n");
				}
				else{
					fprintf(archivoDot, "\t%i->%i [label = \"%i\"];\n");
				}
				auxNodo = auxNodo->sig;
			}
		}
	fprintf(archivoDot, "};\n");
	fclose(archivoDot);
	}
	
	return 1;
}

/*
* Funcion que representara el grafo antes de 
* ser procesado por Dijkstra.
*/

int imprimirGrafoSeba(grafo *g){
	if(g->nVertices == 0){
		printf("No hay que imprimir\n");
		return 0;
	}
	else{
		FILE *archivo = fopen("grafo.dot","w");
		fprintf(archivo, "digraph grafoHermojo {\n");
		fprintf(archivo, "\trankdir=LR;\n");
		fprintf(archivo, "\tnode [style = filled, fillcolor = white, fontcolor = black];\n");
		fprintf(archivo, "\tedge [color = black];\n");
		for(int i = 0; i < g->nVertices; i++){
			nodo *auxNodo = g->arreglo[i].vecino;
			while(auxNodo != NULL){
				int referencia = auxNodo->numNodo;
				fprintf(archivo, "\t%s->%s [label = %i];\n",g->arreglo[i].info,g->arreglo[referencia].info, auxNodo->peso);
				auxNodo = auxNodo->sig;
			}
		}
		fprintf(archivo, "};\n");
		fclose(archivo);
	}
	return 1;
}
