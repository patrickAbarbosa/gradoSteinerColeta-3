#include "../Headers/Fila.h"
#include "../Headers/Vertice.h"

Fila::Fila(){

	primeiro = NULL;
	ultimo = NULL;
}

Fila::~Fila(){

	Vertice * p;
	do{
		p = retira();
	}
	while(p != NULL);
}

bool Fila::vazia(){

	if(primeiro == NULL)
		return true;
	else
		return false;

}

void Fila::insere(Vertice * p){ //entra no final da fila

	if(ultimo == NULL){ //fila vazia
		ultimo = p;
		primeiro = ultimo;
	}
	else{
		Vertice * aux;
		aux = p;
		ultimo->setProx(aux);
		ultimo = aux;
	}
}

Vertice * Fila::retira(){ //sai no começo da fila

	if(primeiro == NULL) //fila vazia
		return NULL;
	else
	{
		Vertice * p = primeiro;
		primeiro = p->getProx();
		if(!primeiro)
			ultimo = NULL;
		return p;
	}
}