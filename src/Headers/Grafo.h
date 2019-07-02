#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "Lista.h"
#include "Vertice.h"
#include "GeraCsv.h"

using namespace std;

class Grafo
{
public:
  Grafo();
  Grafo(string in);
  Grafo(string in, GeraCsv *out);
  Grafo(string in, GeraCsv *out, string ehDigrafo);
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
  bool buscaPorLargura(string verticeInicial,string verticeFinal);
  Vertice **ordenacaoTopologica();
  Grafo * complementar();

  int algoritmoDijkstra(string origem, string destino);
  Grafo* algoritmoPrim();
  Grafo * algoritmoKruskal();

  int algoritmoFloyd(string origem, string destino);
  int auxFloyd(Vertice *p, Vertice* destino);
  //resolucao do problema de steiner

  int custoSteiner (Grafo * arvore);
  int auxGuloso(Vertice * p, Grafo * resultado, int *count, vector<string> *nosLidos);
  Grafo * guloso(string vertice_inicial);
  Grafo * gulosoRandomizado (float alfa);
  // Método para encontrar a melhor solução do Grafo de maneira Gulosa Randomicamente Reativa
  Grafo * gulosoRandomizadoReativo(float *alpha, int nAlphas, int periodos, int bloco);
  
  private:
    Lista  *vertices; // Vetor com os vertices do Grafo
 
    string *arquivoIn; // Estacia de entrada
    
    int numeroArestas;
    int numeroVertices;
    int quantidadeGrausZero;

    //Se verdadeiro é um digrafo
    bool ehDigrafo;
    //Aresta de menor valor
    Aresta *menorValor; 
    // exporta pra csv
    GeraCsv *out;

    //private functions
    // Lê a instância e insere as informaçõe no grafo
    void leArquivo();
    // exporta as informações do grafo para um arquivo .txt 
    void exportGrafo();
    // auxilia a busca por profundidade, recebe o vertice atual e um vetor dos nós já visitados 
    void auxBuscaPorProfundidade(Vertice *vertice, vector <string> *nosLidos); 
    bool ehConexo();
    void auxAddAresta(Vertice *a,  Vertice *b, int peso);
    int auxOrdenacaoTopologica(int vet[], int tam);
    Vertice** montaVetorVertices(int *cont, int tam);
};

#endif // GRAFO_H_INCLUDED
