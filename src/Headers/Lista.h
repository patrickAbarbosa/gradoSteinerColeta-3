#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "./Vertice.h"

using namespace std;

class Lista {
	
	public:
	
		Lista();
		~Lista();
		void insereVertice (string info, int peso);
		void deletaVertice (string info);
		Vertice * buscaVertice (string info);
		Vertice * getMaiorGrau () { return maiorGrau; }		
	
	private:
	
		Vertice * primeiro;
		Vertice * maiorGrau;
		int quantidade; 
		
};

#endif
