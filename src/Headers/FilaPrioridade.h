#ifndef FILAPRIORIDADE_H_INCLUDED
#define FILAPRIORIDADE_H_INCLUDED

#include <iostream>
#include "Aresta.h"

using namespace std;

class FilaPrioridade {

    public:
    	FilaPrioridade();
    	~FilaPrioridade();
    	void insere(Vertice * p);
    	Vertice * retira();
    	bool vazia();
	
    private:
    // Guarda o endereço da primeira aresta da fila
		Vertice * primeiro;
    // Guarda o endereço da ultima aresta da fila
		Vertice * ultimo;
    int tam;
};
#endif // Fila_H_INCLUDED