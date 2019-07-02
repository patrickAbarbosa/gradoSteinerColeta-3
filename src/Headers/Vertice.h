#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Aresta.h"
#include <iostream>

using namespace std;

class Aresta;

class Vertice{

	public:
		Vertice(){};
		Vertice(string id, int peso);
		~Vertice();
		
		string getInfo () { return info; }
		int getGrau () { return grau; }
		int getPeso () { return peso; }
		int getTamCaminho(){ return tamCaminho; }
		void setTamCaminho(int tamanho) { tamCaminho = tamanho; }
		
		void setProx (Vertice * prox) { proximo = prox; } 
		Vertice * getProx () { return proximo; }
		
		void insereAresta (Aresta * a);
		void deletaAresta (Aresta * a);
		
		Aresta * getListaAdjacencia () { return listaAdjacencia; }
		Aresta * buscaAresta(string adjacente);
		
	private:
		int grau;
		int peso;
		int tamCaminho;
		string info;
		Vertice * proximo;
    Aresta * listaAdjacencia;
 
};

#endif //VERTICE_H_INCLUDED
