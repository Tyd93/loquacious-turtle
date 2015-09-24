#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef GRAFO_H
#include "libc\grafo.h"
#define GRAFO_H
#endif

#define VERTEX 8 //Numero de vertices en el grafo.

/*
* A dia 15-09-15, el main solo tiene 
* conexiones de prueba.
* Funcionando al 100%.
*/

int main(int argc, char const *argv[]){
	grafo *g1;
	g1 = crearGrafo(VERTEX);
	cargarGrafo(g1);
	agregaConexion(g1,0,1,10);
	agregaConexion(g1,0,2,11);
	agregaConexion(g1,0,3,12);
	agregaConexion(g1,0,4,13);
	agregaConexion(g1,0,5,14);
	agregaConexion(g1,0,6,15);
	agregaConexion(g1,2,3,16);
	imprimirGrafo(g1);
	return 0;
}

/*
* Cambiare pesoTotal hacia los vertices
* en lugar de los nodos.
* 22/09/15 21:41
*/