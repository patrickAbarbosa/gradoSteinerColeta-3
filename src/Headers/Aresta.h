#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include "Vertice.h"
#include <iostream>

using namespace std;

class Vertice;

class Aresta {

	public:
		Aresta() {peso = 0;};
		Aresta(Vertice * a,Vertice * b, int p) { peso = p, origem = a, adjacente = b, proxima = NULL;};
		~Aresta() {};
		int getPeso () { return peso; };
		Vertice * getAdjacente () { return adjacente; };
		Vertice * getOrigem() { return origem; };
		void setProx (Aresta * prox) { proxima = prox; };
		Aresta * getProx () { return proxima; };
		
	private:
		int peso;
		Vertice * adjacente;
		Vertice * origem;
		Aresta * proxima;
		
};

#endif //ARESTA_H_INCLUDED
