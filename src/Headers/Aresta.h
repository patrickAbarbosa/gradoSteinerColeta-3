#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include "Vertice.h"
#include <iostream>

using namespace std;

class Vertice;

class Aresta {
	
	public:
		Aresta() {};
		Aresta(Vertice * a, int p) { peso = p, adjacente = a, proxima = NULL;} 
		~Aresta() {};
		int getPeso () { return peso; }
		Vertice * getAdjacente () { return adjacente; }
		void setProx (Aresta * prox) { proxima = prox; }  
		Aresta * getProx () { return proxima; }
		
	private:
		int peso;
		Vertice * adjacente;
		Aresta * proxima;
		
};

#endif //ARESTA_H_INCLUDED
