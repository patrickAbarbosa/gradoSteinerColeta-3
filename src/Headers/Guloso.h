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
<<<<<<< HEAD
	void auxCalculaGuloso(Vertice *atual, int *n);
	//Gera a AGM a partir do Grafo
	Grafo *geraGrafo();
	
=======
	bool arestaLida(Aresta * a);
>>>>>>> 33715af47b487a2e61ce9722cf4b9ece8611ffad
};
#endif // GULOSO_H