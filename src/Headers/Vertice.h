#ifndef VERTICE_H
#def VERTICE_H

#include Aresta.h

using namespace std;

Class Vertice{

	public:
	
		Vertice(string id, int peso);
		~Vertice();
		
		int getGrau () { return grau; }
		string getInfo () { return info; }
		int getPeso () { return peso; }
		void setProx (Vertice * prox) { proximo = prox; } 
		Vertice * getProx () { return proximo; }
		
		void insereAresta ();
		void deletaAresta ();
		Aresta * getListaAdjacencia () { return listaAdjacencia; }

	private:
	
		int grau;
		int peso;
		string info;
		Vertice * proximo;
        Aresta * listaAdjacencia;
     
}

#endif
