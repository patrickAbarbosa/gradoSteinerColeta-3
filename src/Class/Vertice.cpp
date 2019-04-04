#include "../Headers/Vertice.h"

//Contrutor padrao de vertices utilizando um id e um peso_vertice

Vertice::Vertice(string id, int peso_vertice) {
	
	info = id;
	peso = peso_vertice;
	proximo = NULL;
	
}

Vertice::~Vertice(){
	
}

void Vertice::insereAresta() {
	
}

void Vertice::deletaAresta() {
	
}
