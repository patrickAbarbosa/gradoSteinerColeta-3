#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Aresta.h"
#include <iostream>

using namespace std;

class Aresta;

class Vertice{

	public:
		Vertice(string id, int peso);
		~Vertice();
		
		string getInfo () { return info; }
		int getGrau () { return grau; }
		int getPeso () { return peso; }
		
		void setProx (Vertice * prox) { proximo = prox; } 
		Vertice * getProx () { return proximo; }
		
		void insereAresta (Aresta * a);
		void deletaAresta (Aresta * a);
		
		Aresta * getListaAdjacencia () { return listaAdjacencia; }

	private:
		int grau;
		int peso;
		string info;
		Vertice * proximo;
        Aresta * listaAdjacencia;
     
};

#endif //VERTICE_H_INCLUDED
