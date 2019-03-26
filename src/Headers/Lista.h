#ifndef LISTA_H
#define LISTA_H

#include Vertice.h

using namespace std;

Class Lista {
	
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
		
}

#endif