#include <iostream>
#include "../Headers/Vertice.h"

using namespace std;
//Contrutor padrao de vertices utilizando um id e um peso_vertice

Vertice::Vertice()
{
	peso = 0;
	proximo = NULL;
	grau = 0;
	tamCaminho = 0;
}


Vertice::Vertice(string id, int peso_vertice)
{
	info = id;
	peso = peso_vertice;
	grau = 0;
	tamCaminho = 0;
}

Vertice::~Vertice()
{	
}

void Vertice::insereAresta(Aresta * a)
{
	adjacentes.push_back(a);
}

void Vertice::deletaAresta(Aresta * a)
{
	adjacentes
}

Aresta * Vertice::buscaAresta(string adjacente){
	
	Aresta * p = adjacentes;
	
	while( p != NULL) {
		Vertice * t = p->getAdjacente();
		if( t->getInfo() == info)
			return p;
		p = p->getProx();
	}
	
	return NULL;
}
