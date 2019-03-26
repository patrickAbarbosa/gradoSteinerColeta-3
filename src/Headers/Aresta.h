#ifndef ARESTA_H
#define ARESTA_H

#include "../Headers/Vertice.h"

Class Aresta {
	
	public:
	
		Aresta();
		~Aresta();
		
		int getPeso () { return peso; }
		Vertice * getAdjacente () { return adjacente; }
		void setProx (Aresta * prox) { proxima = prox; }  
		Aresta * getProx () { return proxima; }
		
	private:
	
		int peso;
		Vertice * adjacente;
		Aresta * proxima;
		
}

#endif
