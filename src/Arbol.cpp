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
		fprintf(dot,"%i [label=\"%c\"];\n",a->getPosicion(),a->getDato());
		countInordenPosicion++;
    }

};

void Arbol::setLabelAFNDOT(Arbol *a,FILE *dot){
	if(a!=NULL){
		setLabelAFNDOT(a->hojaIzquierda,dot);
		setLabelAFNDOT(a->hojaDerecha,dot);
		fprintf(dot,"\n%i [label=\"%c\"];\n",a->getPosicion(),' ',a->getDato());
		fprintf(dot,"\n%i [label=\"%c\"];\n",a->getPosicion()+100,' ',a->getDato());
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
				a->setIni(a->hojaIzquierda->getIni());
				a->setFin(a->hojaDerecha->getFin());
				a->hojaDerecha->setIni(a->hojaIzquierda->getFin());
				break;
			case '|':
				a->setIni(a->getPosicion());
				a->setFin(a->getIni()+100);
				a->setEstadoInicial(a->hojaIzquierda->getIni(),0);
				a->setEstadoInicial(a->hojaDerecha->getIni(),1);
				
				a->hojaIzquierda->setEstadoFinal(a->getFin(),0);
				a->hojaDerecha->setEstadoFinal(a->getFin(),0);
				break;
			case '+':
				a->setIni(a->getPosicion());
				a->setFin(a->getIni()+100);
				a->setEstadoInicial(a->hojaIzquierda->getIni(),0);
				a->hojaIzquierda->setEstadoFinal(a->getFin(),0);
				a->hojaIzquierda->setEstadoFinal(a->hojaIzquierda->getIni(),1);
				break;
			case '*':
				a->setIni(a->getPosicion());
				a->setFin(a->getIni()+100);
				a->setEstadoInicial(a->hojaIzquierda->getIni(),0);
				a->setEstadoInicial(a->getFin(),1);
				a->hojaIzquierda->setEstadoFinal(a->getFin(),0);
				a->hojaIzquierda->setEstadoFinal(a->hojaIzquierda->getIni(),1);
				break;
			default:
					a->setIni(a->getPosicion());
					a->setFin(a->getIni()+100);
					a->setEstadoInicial(a->getFin(),0);
				break;
		}
	}
};

void Arbol::dibujarAutomata(Arbol *a,FILE *dot){
	if(a!=NULL){
		dibujarAutomata(a->hojaIzquierda,dot);
		dibujarAutomata(a->hojaDerecha,dot);
		
		if(a->getDato()!='.'&&a->getDato()!='|'&&a->getDato()!='*'&&a->getDato()!='+'){
		
			if(a->getDato()!='.'){	
				if(a->getEstadoInicial(1)!=-1)
					fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*2-%c*/\n",a->getIni(),a->getEstadoInicial(1),a->getDato(),a->getDato());
				
				if(a->getEstadoInicial(0)!=-1){
					fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*1-%c*/\n",a->getIni(),a->getEstadoInicial(0),a->getDato(),a->getDato());
					
					if(a->getEstadoFinal(0)!=-1)
						fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*3-%c*/\n",a->getFin(),a->getEstadoFinal(0),'e',a->getDato());
					
					if(a->getEstadoFinal(1)!=-1)
						fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*4-%c*/\n",a->getEstadoInicial(0),a->getEstadoFinal(1),'e',a->getDato());
				}
			}if(a->getDato()=='.'&&a->getEstadoFinal(0)>0)
				fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*5-%c*/\n",a->hojaDerecha->getFin(),a->getEstadoFinal(0),'e',a->getDato());
			
		}else{
			
			if(a->getDato()!='.'){	
				if(a->getEstadoInicial(1)!=-1)
					fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*2-%c*/\n",a->getIni(),a->getEstadoInicial(1),'e',a->getDato());
				
				if(a->getEstadoInicial(0)!=-1){
					fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*1-%c*/\n",a->getIni(),a->getEstadoInicial(0),'e',a->getDato());
					
					if(a->getEstadoFinal(0)!=-1)
						fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*3-%c*/\n",a->getFin(),a->getEstadoFinal(0),'e',a->getDato());
					
					if(a->getEstadoFinal(1)!=-1)
						fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*4-%c*/\n",a->getEstadoInicial(0),a->getEstadoFinal(1),'e',a->getDato());
				}
			}if(a->getDato()=='.'&&a->getEstadoFinal(0)>0)
				fprintf(dot,"\t%i -> %i [label=\"%c\"];\t/*5-%c*/\n",a->hojaDerecha->getFin(),a->getEstadoFinal(0),'e',a->getDato());
			
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
void Arbol::setIni(int e){
	d.setIni(e);
};
int  Arbol::getIni(void){
	return d.getIni();
};
void Arbol::setFin(int e){
	d.setFin(e);
};
int  Arbol::getFin(void){
	return d.getFin();
};
void Arbol::setEstadoInicial(int edo,int i){
	d.setEstadoInicial(edo,i);
};
void Arbol::setEstadoFinal(int edo,int i){
	d.setEstadoFinal(edo,i);
};
int Arbol::getEstadoInicial(int i){
	return d.getEstadoInicial(i);
};
int Arbol::getEstadoFinal(int i){
	d.getEstadoFinal(i);
};