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

//	Grafo * calculaGuloso(string verticeInicial);
	Grafo * calculaGuloso(Vertice *inicial);
	Grafo * gulosoRandomizado (float alfa, int numeroInteracoes);
	Grafo * algoritmoPrim(Vertice * inicial);
	Grafo * gulosoRandomizadoReativo(float *alpha, int nAlphas, int periodos, int bloco);

private: 
	// Guarda o custo total da solução
	int custoSolucao;
	// Guarda o custo a pagar.
	int custoPagar;

	// Guarda o número de vertices do grafo
	int tam;

	Grafo *grafo;

	// verifica se o vertice foi lido e retorna sua posição
	int lido(string val);
	void auxCalculaGuloso(Vertice *atual, int *n);
	//Gera a AGM a partir do Grafo
	Grafo *geraGrafo();
	
	bool arestaLida(Aresta * a);
};
#endif // GULOSO_H