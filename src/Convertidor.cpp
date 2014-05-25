#include "Convertidor.hpp"

void Convertidor::expresionPostFija(char *e){
	Expresion expExtendida;
	Pila p,o;
	int i;
	exp.concatenar(e);
	//exp.concatenar("(",exp,").#");
	for(i=exp.tamExp()-1;i>=0;i--){
		switch(exp.extraer(i)){
			case '|':
			case '+':
			case '*':
			case '.':	
			case ')':
				o.push(exp.extraer(i));
				break;
				
			case '(':
				while(o.top()!=')'){
					p.push(o.top());
					o.pop();
				}o.pop();
				break;
								
			default:
				p.push(exp.extraer(i));
				if(!o.esVacia()){
					if(o.top()=='+'||o.top()=='*'){
						p.push(o.top());
						o.pop();
					}
				}break;
		}
	}while(!o.esVacia()){
		p.push(o.top());
		o.pop();
	}printf("\nNotación Postfija de la expresión regular: \n");
	while(!p.esVacia()){
		expExtendida.concatenar(p.top());
		printf("%c",p.top());
		p.pop();
	}printf("\n");
	exp=expExtendida;
};

void Convertidor::construirArbol(void){
	int i;
	char temp;
	arbolSintactico=NULL;
	for(i=0;i<exp.tamExp();i++){
		temp=exp.extraer(i);
		arbolSintactico->insertar(&arbolSintactico,temp);
	}printf("\nArbol sintactico: ");
	arbolSintactico->inorden(arbolSintactico);
	printf("\n");
};

void Convertidor::dibujarArbol(void){
	FILE *dot;
	dot = fopen ( "arbol.dot", "w" );
	fprintf(dot,"graph Arbol{\n");
	arbolSintactico->setLabelDOT(arbolSintactico,dot);
	arbolSintactico->postordenConstruir(arbolSintactico,dot);
	fprintf(dot,"}");	
	fclose ( dot );
	system("dot -Tjpg -O  arbol.dot");
	system("ristretto arbol.dot.jpg");
	
};

void Convertidor::construirAutomata(void){
	arbolSintactico->construirAutomata(arbolSintactico);
};

void Convertidor::dibujarAutomata(void){
	FILE *dot;
	dot = fopen ( "afn.dot", "w" );
	fprintf(dot,"digraph AFN{\n");
	//arbolSintactico->setLabelAFNDOT(arbolSintactico,dot);
	arbolSintactico->dibujarAutomata(arbolSintactico,dot);
	fprintf(dot,"}");	
	fclose ( dot );
	system("dot -Tjpg -O  afn.dot");
	system("ristretto afn.dot.jpg");
};

void Convertidor::marcarEstados(void){};

