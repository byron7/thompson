#ifndef __DATO_HPP__
#define __DATO_HPP__

#include <iostream>

class Dato{
	private:
// Se guardará el caractér de interés del árbol sintáctico,
// la posición de los símbolos, si es anulable o no,
// y una lista para los nodos primeros y últimos.
		char d;
		int posicion;
		int estadoInicial[2];
		int estadoFinal;
	public:
// Inicializa el objeto Dato.
		Dato();
// Consulta el dato.
		char getDato();
// Almacena el valor del caractér.
		void setDato(char);
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
