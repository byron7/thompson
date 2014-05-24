#include "Aplicacion.hpp"

void Aplicacion::iniciar(int argc, char *argv[]){
	if(argc==2){
		Convertidor c;
		printf("\nExpresion a convertir: \n%s\n",argv[1]);
		
		c.expresionPostFija(argv[1]);
		c.construirArbol();
		c.dibujarArbol();
		c.construirAutomata();
		c.dibujarAutomata();
		
	}else
		std::cout << "Error de entrada."<<std::endl;

};