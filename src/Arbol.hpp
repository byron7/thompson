#ifndef __ARBOL_HPP__
#define __ARBOL_HPP__

#include <stdio.h>

#include "Dato.hpp"

static int countInordenPosicion=1;
static int countAutomata=1;

class Arbol{
	private:
// Cada árbol contendrá un campo para guardar el dato y 
// 2 apuntadores a un arbol hijo izquierdo y uno derecho.
		Dato d;
		Arbol *hojaIzquierda;
		Arbol *hojaDerecha;
	public:
// Inicializa los arboles hijos en NULL
		Arbol();
// Inserta cada caracter de la expresión regular en el árbol sintáctico.
		bool insertar(Arbol**,char);
		void inorden(Arbol*);
// Recorre el árbol sintáctico con un recorrido "postorden". 
// (hojaIzquierda, hojaDerecha, raíz)
		void setLabelDOT(Arbol*,FILE*);
		void postordenConstruir(Arbol*,FILE*);
		void construirAutomata(Arbol*);
		void dibujarAutomata(Arbol*,FILE*);
		
// Coloca el caractér dentro del nodo raíz.
		void setDato(char);
// Consulta el dato (caractér) del nodo raíz.
		char getDato(void);
// Coloca la posición de los símbolos que están en la expresión regular.
		void setPosicion(int);
// Consulta la posición del nodo.
		int getPosicion();

		void setEstadoInicial(int,int);
		void setEstadoFinal(int);
		int getEstadoInicial(int);
		int getEstadoFinal();
};

#endif
