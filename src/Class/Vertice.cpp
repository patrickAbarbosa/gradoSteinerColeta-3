#include <iostream>
#include "../Headers/Vertice.h"

using namespace std;
//Contrutor padrao de vertices utilizando um id e um peso_vertice

Vertice::Vertice(string id, int peso_vertice)
{
	info = id;
	peso = peso_vertice;
	proximo = NULL;
	listaAdjacencia = NULL;
	grau = 0;
	tamCaminho = 0;
}

Vertice::~Vertice()
{
	while(listaAdjacencia != NULL){
		Aresta * p = listaAdjacencia->getProx();
		delete p;
		listaAdjacencia = p;
	}
	//deletar lista de arestas
	
}

void Vertice::insereAresta(Aresta * a)
{
	if(listaAdjacencia == NULL){
		listaAdjacencia = new Aresta();
		*listaAdjacencia = *a; 
		// cria uma copia da aresta para nao dar erro com o ponteiro para o proximo
	}
	else{
		Aresta * p = new Aresta();
		Aresta * t = listaAdjacencia;
		*p= *a;
		 
		while(t->getProx()!=NULL)
			t = t->getProx();
		t->setProx(p);
	}
	grau++;
}

void Vertice::deletaAresta(Aresta * a)
{
	Aresta * p = listaAdjacencia;
	
	while(p!=NULL){
		Aresta * t = p->getProx();
		if(t->getAdjacente() == a->getAdjacente()){
			t = p->getProx();
			p->setProx(a->getProx());
			delete t;
		}
	}
}

Aresta * Vertice::buscaAresta(string adjacente){
	
	Aresta * p = listaAdjacencia;
	
	while( p != NULL) {
		Vertice * t = p->getAdjacente();
		if( t->getInfo() == info)
			return p;
		p = p->getProx();
	}
	
	return NULL;
}
