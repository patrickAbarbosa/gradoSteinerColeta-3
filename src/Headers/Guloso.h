#ifndef GULOSO_H_INCLUDED
#define GULOSO_H_INCLUDED

#include <iostream>
#include "Vertice.h"
#include "Grafo.h"

using namespace std;

class Guloso {
public:
	Guloso(Grafo *g);
	~Guloso();
	
	// Calcula custo do grafo
	int calculaCustoGrafo(Grafo *g);

	Grafo * calculaGuloso(string verticeInicial);
	Grafo * gulosoRandomizado (float alfa);
	Grafo * algoritmoPrim(Vertice * inicial);

private: 
	// Guarda o custo total da solução
	int custoSolucao;
	// Guarda o custo a pagar.
	int custoPagar;

	// Guarda o número de vertices do grafo
	int tam;
	// Guarda o indice do ultimo vertice
	int ultimo;
	//guarda o indice da ultima aresta
	int ultimaAresta;
	// Guarda a informação dos vertices lidos
	Vertice **vetInfoVertice;
	// Guarda as arestas utilizadas
	Aresta ** vetArestaIncidente;

	Grafo *grafo;

	// verifica se o vertice foi lido e retorna sua posição
	int lido(string val);
	bool arestaLida(Aresta * a);
};
#endif // GULOSO_H