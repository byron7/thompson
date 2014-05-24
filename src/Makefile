sal:main

main: Aplicacion.o Arbol.o Convertidor.o Dato.o Expresion.o Nodo.o Pila.o main.o
	g++ Aplicacion.o Arbol.o Convertidor.o Dato.o Expresion.o Nodo.o Pila.o main.o -o main

Aplicacion.o:Aplicacion.cpp
			g++ -c Aplicacion.cpp	

Arbol.o:Arbol.cpp
			g++ -c Arbol.cpp	

Convertidor.o:Convertidor.cpp
			g++ -c Convertidor.cpp	

Dato.o:Dato.cpp
			g++ -c Dato.cpp	

Expresion.o:Expresion.cpp
			g++ -c Expresion.cpp	

Nodo.o:Nodo.cpp
			g++ -c Nodo.cpp							

Pila.o:Pila.cpp
			g++ -c Pila.cpp	
main.o: main.cpp
			g++ -c main.cpp

clean :rm -rf *o main