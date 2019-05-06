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

  //Public fnctions

  void addAresta(string id_a, string id_b, int peso);
  void deletaAresta(string id_a, string id_b);
  void imprimeGrafoPNG();
  void menuSelecionado(char a);
  void menu();

  void buscaPorProfundidade(string verticeInicial);
  void buscaPorLargura(string verticeInicial);
  Grafo *complementar();

  private:
    Lista  *vertices;
 
    string *arquivoIn;
    string *arquivoOut;
    
    int numeroArestas;
    int numeroVertices;

    bool ehDigrafo;

    Data *db;
    //private functions
    void leArquivo();
    void exportGrafo();
    void auxBuscaPorProfundidade(Vertice *vertice, vector <string> *nosLidos);
    bool ehConexo();
    void auxAddAresta(Vertice *a,  Vertice *b, int peso);
    void auxComplementar(Vertice *v, Grafo *g);
};

#endif // GRAFO_H_INCLUDED
