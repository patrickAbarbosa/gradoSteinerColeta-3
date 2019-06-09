#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "Vertice.h"

using namespace std;

class Lista {
	
	public:
		Lista();
		~Lista();
		void insereVertice (string info, int peso);
		void deletaVertice (string info);
		Vertice * getPrimeiro() { return primeiro;}
		Vertice * buscaVertice (string info);
		void setMaiorGrau(Vertice * maior) { maiorGrau = maior;}
		Vertice * getMaiorGrau () { return maiorGrau; }
		int getQuantidade() { return quantidade;}		
	
	private:
		Vertice * primeiro;
		Vertice * maiorGrau;
		int quantidade; 
		
};

#endif //LISTA_H_INCLUDED
