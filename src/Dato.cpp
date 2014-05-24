#include "Dato.hpp"

Dato::Dato(){
	posicion=0;
	estadoInicial[0]=-1;
	estadoInicial[1]=-1;
	estadoFinal=-1;
};
char Dato::getDato(){
	return d;	
};

void Dato::setDato(char c){
	d=c;
};

void Dato::setPosicion(int pos){
	posicion=pos;
};

int Dato::getPosicion(){
	return posicion;
};

void Dato::setEstadoInicial(int edo,int i){
	estadoInicial[i]=edo;
};

void Dato::setEstadoFinal(int edo){
	estadoFinal=edo;
};

int Dato::getEstadoInicial(int i){
	return estadoInicial[i];
};

int Dato::getEstadoFinal(){
	return estadoFinal;
};