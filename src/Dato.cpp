#include "Dato.hpp"

Dato::Dato(){
	posicion=0;
	estadoInicial[0]=-1;
	estadoInicial[1]=-1;
	estadoFinal[0]=-1;
	estadoFinal[1]=-1;
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
void Dato::setIni(int e){
	eIni=e;
};
int  Dato::getIni(void){
	return eIni;
};
void Dato::setFin(int e){
	eFin=e;
};
int  Dato::getFin(void){
	return eFin;
};
void Dato::setEstadoInicial(int edo,int i){
	estadoInicial[i]=edo;
};
void Dato::setEstadoFinal(int edo,int i){
	estadoFinal[i]=edo;
};
int Dato::getEstadoInicial(int i){
	return estadoInicial[i];
};
int Dato::getEstadoFinal(int i){
	return estadoFinal[i];
};