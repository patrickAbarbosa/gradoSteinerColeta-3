#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Aresta.h"
#include <iostream>
#include <vector>

using namespace std;

class Aresta;

class Vertice{

	public:
		//construtor do vertice
		Vertice();
		//construtor do vertice
		Vertice(string id, int peso);
		//Destrutor do vertice
		~Vertice();
		//Altera informação do vertce
		void setInfo(string info){this->info = info;};
		//Altera o peso do vertice
		void setPeso(int peso){this->peso = peso;};
		//Retorna a informação do vertice
		string getInfo () {return info;}
		//Retorna o grau do vertice
		int getGrau () {return grau;}
		//Retorna o peso do vertice
		int getPeso () { return peso; }
		
		int getTamCaminho(){ return tamCaminho; }
		void setTamCaminho(int tamanho) { tamCaminho = tamanho; }
		
		void setProx (Vertice * prox) { proximo = prox; } 
		Vertice * getProx () { return proximo; }
		
		void insereAresta (Aresta * a);
		void deletaAresta (Aresta * a);
		
		Aresta * getListaAdjacencia () { return adjacentes; }
		Aresta * buscaAresta(string adjacente);
		
	private:
		int grau;
		int peso;
		int tamCaminho;
		string info;
		Vertice * proximo;
    vector<Aresta*> adjacentes;
 
};

#endif //VERTICE_H_INCLUDED
