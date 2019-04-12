#include "../Headers/Vertice.h"

//Contrutor padrao de vertices utilizando um id e um peso_vertice

Vertice::Vertice(string id, int peso_vertice)
{
	info = id;
	peso = peso_vertice;
	proximo = NULL;
	listaAdjacencia = NULL;
}

Vertice::~Vertice()
{
	//deletar lista de arestas
	
}

void Vertice::insereAresta(Aresta * a)
{
	if(listaAdjacencia == NULL){
		listaAdjacencia = new Aresta();
		*listaAdjacencia = *a; 
		// cria uma copia da aresta para nao dar erro com o ponteiro para o proximo
	}
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
