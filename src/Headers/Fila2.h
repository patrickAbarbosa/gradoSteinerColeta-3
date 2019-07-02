#ifndef FILA2_H_INCLUDED
#define FILA2_H_INCLUDED

#include <iostream>
#include "Vertice.h"
#include "NoFila2.h"

using namespace std;

class Fila2 {

    public:
    	Fila2();
    	~Fila2();
    	void insere(Vertice * p);
    	Vertice * retira();
    	bool vazia();
	
    private:
		NoFila2 * primeiro;
		NoFila2 * ultimo;
};
#endif // Fila2_H_INCLUDED