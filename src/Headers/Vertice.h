#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Aresta.h"
#include <iostream>

using namespace std;

class Aresta;

class Vertice
{

public:
	Vertice(string id, int peso);
	virtual ~Vertice();

	int getGrau() { return grau; }
	string getInfo() { return info; }
	int getPeso() { return peso; }
	void setProx(Vertice *prox) { proximo = prox; }
	Vertice *getProx() { return proximo; }

	void insereAresta();
	void deletaAresta();
	Aresta *getListaAdjacencia() { return listaAdjacencia; }

private:
	int grau;
	int peso;
	string info;
	Vertice *proximo;
	Aresta *listaAdjacencia;
};

#endif
