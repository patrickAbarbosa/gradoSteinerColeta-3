#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "Lista.h"
#include "Vertice.h"

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
  
  private:
    Lista  *vertices;
 
    string *arquivoIn;
    string *arquivoOut;
    
    int numeroArestas;
    int numeroVertices;

    bool ehDigrafo;

    //private functions
    void leArquivo();
    void exportGrafo();
    void auxBuscaPorProfundidade(Vertice *vertice, vector <string> *nosLidos);
    
};

#endif // GRAFO_H_INCLUDED
