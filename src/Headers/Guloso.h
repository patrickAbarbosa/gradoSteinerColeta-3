#ifndef GULOSO_H_INCLUDED
#define GULOSO_H_INCLUDED

#include <iostream>
#include "Vertice.h"
#include "Grafo.h"
#include "NoGuloso.h"

using namespace std;

class Guloso {
public:
	Guloso(Grafo *g);
	~Guloso();
	
	// Calcula custo do grafo
	int calculaCustoGrafo(Grafo *g);

	Grafo *calculaGuloso(string verticeInicial);

private: 
	// Guarda o custo total da solução
	int custoSolucao;
	// Guarda o custo a pagar.
	int custoPagar;

	// Guarda o número de vertices do grafo
	int tam;
	// Guarda o indice do ultimo vertice
	int ultimo;
	// Guarda o indice do ultimo no Guloso
	int ultimoNoGuloso;
	// Guarda a informação dos vertices lidos
	Vertice **vetInfoVertice;
	// Guarda o vertor de aresta e vertice de partida
	NoGuloso *vetArestaIncidente;

	Grafo *grafo;

	// verifica se o vertice foi lido e retorna sua posição
	int lido(string val);
	void auxCalculaGuloso(Vertice *atual);
	//Gera a AGM a partir do Grafo
	Grafo *geraGrafo();
};
#endif // GULOSO_H