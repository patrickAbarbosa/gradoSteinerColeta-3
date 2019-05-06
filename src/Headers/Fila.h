#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <iostream>
#include "Vertice.h"
using namespace std;

class Fila {

    public:
    	Fila();
    	~Fila();
    	void insere(Vertice * p);
    	Vertice * retira();
			bool vazia();
	
    private:
		Vertice * primeiro;
		Vertice * ultimo;
};
#endif // Fila_H_INCLUDED