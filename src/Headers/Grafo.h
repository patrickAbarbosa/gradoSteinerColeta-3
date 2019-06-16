#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "Lista.h"
#include "Vertice.h"
#include "./Data.h"

using namespace std;

class Grafo
{
public:
  Grafo();
  Grafo(string in);
  Grafo(string in, string out);
  Grafo(string in, string out, string ehDigrafo);
  ~Grafo();

  //Public functions
  
  void addAresta(string id_a, string id_b, int peso);
  void deletaAresta(string id_a, string id_b);
  void imprimeGrafoPNG();
  void menuSelecionado(char a);
  void menu();
  Lista * getVertices(){ return vertices;}

  void atualizaMaiorgrau();
  Vertice * buscaVertice(int i);
  void buscaPorProfundidade(string verticeInicial);
  void buscaPorLargura(string verticeInicial);
  Vertice **ordenacaoTopologica();
  Grafo * complementar();

  int algoritmoDijkstra(string origem, string destino);
  Grafo* algoritmoPrim();
  Grafo * algoritmoKruskal();

  int algoritmoFloyd(string origem, string destino);
  int auxFloyd(Vertice *p, Vertice* destino);
  //resolucao do problema de steiner

  int custoSteiner (Grafo * arvore);
  int auxGuloso(Vertice * p, Grafo * resultado, int count);
  Grafo * guloso(string vertice_inicial);
  Grafo * gulosoRandomizado (float alfa);
  
  private:
    Lista  *vertices; // Vetor com os vertices do Grafo
 
    string *arquivoIn; // Estacia de entrada
    string *arquivoOut; // Dados pra saida
    
    int numeroArestas;
    int numeroVertices;
    int quantidadeGrausZero;

    bool ehDigrafo; // Se verdadeiro é um digrafo
    Aresta *menorValor; // Aresta de menor valor

    Data *db;

    //private functions
    void leArquivo(); // Lê a instância e insere as informaçõe no grafo
    void exportGrafo(); // exporta as informações do grafo para um arquivo .txt
    void auxBuscaPorProfundidade(Vertice *vertice, vector <string> *nosLidos); 
    bool ehConexo();
    void auxAddAresta(Vertice *a,  Vertice *b, int peso);
    int auxOrdenacaoTopologica(int vet[], int tam);
    Vertice** montaVetorVertices(int *cont, int tam);
};

#endif // GRAFO_H_INCLUDED
