#include "Arbol.hpp"

Arbol::Arbol(){
	hojaIzquierda=NULL;
	hojaDerecha=NULL;
};

bool Arbol::insertar(Arbol **a,char x){
	if(*a!=NULL){
		if((*a)->getDato()=='+'||(*a)->getDato()=='*'||
			(*a)->getDato()=='.'||(*a)->getDato()=='|'){
			if(insertar(&((*a)->hojaIzquierda),x)==true)
				return true;
			if((*a)->getDato()=='.'||(*a)->getDato()=='|')
				insertar(&((*a)->hojaDerecha),x);
		}
    }else{
		(*a)=new Arbol();
		(*a)->hojaIzquierda=NULL;
		(*a)->setDato(x);
		(*a)->hojaDerecha=NULL;
		//printf("\nSe insertó el elemento %c correctamente.",(*a)->getDato());
		return true;
	}
};

void Arbol::inorden(Arbol *a){
	if(a!=NULL){
		inorden(a->hojaIzquierda);
		printf("%c",a->getDato());
		inorden(a->hojaDerecha);
	}
};

void Arbol::setLabelDOT(Arbol *a,FILE* dot){
	if(a!=NULL){
		setLabelDOT(a->hojaIzquierda,dot);
		setLabelDOT(a->hojaDerecha,dot);
		a->setPosicion(countInordenPosicion);
		printf("%c pos: %i\n",a->getDato(),a->getPosicion());
		fprintf(dot,"%i [label=\"%c\"]",a->getPosicion(),a->getDato());
		countInordenPosicion++;
    }

};

void Arbol::postordenConstruir(Arbol *a,FILE *dot){
	if(a!=NULL){
		postordenConstruir(a->hojaIzquierda,dot);
		postordenConstruir(a->hojaDerecha,dot);
		switch(a->getDato()){
			case '.':
			case '|':
				fprintf(dot,"%i -- %i\n",a->getPosicion(),a->hojaIzquierda->getPosicion());
				fprintf(dot,"%i -- %i\n",a->getPosicion(),a->hojaDerecha->getPosicion());
				break;
			case '+':
			case '*':
				fprintf(dot,"%i -- %i\n",a->getPosicion(),a->hojaIzquierda->getPosicion());
				break;
			default:
				break;
				
		}
    }
};
void Arbol::construirAutomata(Arbol *a){
	if(a!=NULL){
		construirAutomata(a->hojaIzquierda);
		construirAutomata(a->hojaDerecha);
		switch(a->getDato()){
			case '.':
				a->setEstadoInicial(a->hojaIzquierda->getPosicion(),0);
				a->hojaIzquierda->setEstadoFinal(a->hojaDerecha->getEstadoInicial(0));
				a->setEstadoFinal(a->hojaDerecha->getEstadoFinal());
				break;
			case '|':
				break;
			case '+':
				break;
			case '*':
				break;
			default:
					a->setEstadoInicial(a->getPosicion(),0);
					a->setEstadoFinal(a->getPosicion()+2);
				break;
		}
	}
};

void Arbol::dibujarAutomata(Arbol *a,FILE *dot){
		if(a!=NULL){
		dibujarAutomata(a->hojaIzquierda,dot);
		dibujarAutomata(a->hojaDerecha,dot);
		countInordenPosicion--;
		switch(a->getDato()){
			case '.':
				fprintf(dot,"\tsubgraph cluster_%i{\n\t\tlabel=\"%c\";\n\t\t%i0 -- %i0 [label=\"%c\"];\n\t\t%i0 -- %i2 [label=\"%c\"];\n\t}\n",
						countInordenPosicion,a->getDato(),a->hojaIzquierda->getPosicion(),a->hojaDerecha->getPosicion(),a->hojaIzquierda->getDato(),a->hojaDerecha->getPosicion(),a->hojaDerecha->getPosicion(),a->hojaDerecha->getDato());
				break;
				
			case '|':
			case '+':
			case '*':
				//fprintf(dot,"\tsubgraph cluster_%i{\n\t\tlabel=\"Subgraph %c\";\n\t\t%i -- %i9;\n\t}\n",countInordenPosicion,a->getDato(),a->getPosicion(),a->getPosicion());
			default:
				//fprintf(dot,"\tsubgraph cluster_%i{\n\t\tlabel=\"%c\";\n\t\t%i -- %i9 [label=\"%c\"];\n\t}\n",countInordenPosicion,' ',a->getPosicion(),a->getPosicion(),a->getDato());
				break;
		}
    }
	
};


void Arbol::setDato(char c){
	d.setDato(c);
};
char Arbol::getDato(void){
	return d.getDato();
};
void Arbol::setPosicion(int pos){
	d.setPosicion(pos);
};
int Arbol::getPosicion(){
	return d.getPosicion();
};
void Arbol::setEstadoInicial(int edo,int i){
	d.setEstadoInicial(edo,i);
};
void Arbol::setEstadoFinal(int edo){
	d.setEstadoFinal(edo);
};
int Arbol::getEstadoInicial(int i){
	return d.getEstadoInicial(i);
};
int Arbol::getEstadoFinal(){
	d.getEstadoFinal();
};