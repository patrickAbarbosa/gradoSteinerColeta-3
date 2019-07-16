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

	bool isVector(vector<string> *vet, string aux);
	Grafo * montaGrafo(vector<Aresta*> * arestas,int custo);
	//guloso
	Grafo * calculaGuloso(string inicial);
	int auxCalculaGuloso(Vertice *inicial, vector<Aresta*> *vetor_arestas);
	int  algoritmoPrim(Vertice * inicial, vector<Aresta*> *vetor_arestas);
	//guloso randomizado
	Grafo * gulosoRandomizado(float alfa, int numeroInteracoes);
	int auxGulosoRandomizado (float alfa, int numeroInteracoes,vector<Aresta *> *vetor_arestas_melhor);
	//guloso randomizado Reativo
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