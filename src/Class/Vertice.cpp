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
	int i = 0;
	vector<Aresta*>::iterator it;
	for(it = adjacentes.begin() ; it != adjacentes.end(); ++it)
		if(*it == a)
			break;
	if(i != adjacentes.size())
		adjacentes.erase(adjacentes.begin() + i);
}

Aresta * Vertice::buscaAresta(string adjacente){
	for(vector<Aresta*>::iterator it = adjacentes.begin() ; it != adjacentes.end(); ++it)
		if((*it)->getAdjacente()->getInfo() == adjacente)
			return *it;
	return NULL;
}
