#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <string>
#include "Lista.h"

#include "../Headers/Lista.h"
#include "../Headers/Vertice.h"

using namespace std;

class Grafo
{
  public:
    Grafo();
    Grafo(string in);
    Grafo(string in, string out);
    ~Grafo();

    //Public fnctions
    
	void addAresta(string id_a, string id_b, int peso);
	void deletaAresta(string id_a, string id_b);
	void imprimeGrafoPNG();
  void menuSelecionado(char a);
  void menu();

  private:
    Lista  *vertices;
 
    string *arquivoIn;
    string *arquivoOut;
    
    int numeroArestas;
    int numeroVertices;

    //private functions
    void leArquivo();
    void exportGrafo();
    void auxBuscaPorProfundidade(Vertice *vertice);
    void buscaPorProfundidade(string verticeInicial);
};

#endif // GRAFO_H_INCLUDED
