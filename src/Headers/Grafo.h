#pragma once
#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <string>

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
    void addVertice(int info, int peso);
    void deleteVertice(int info);

    void addAresta(int origem, int destino, int peso);
    void deleteAresta(int info);

    Vertice *getVertice(int info);

  private:
    Lista  *vertices;
 
    string *arquivoIn;
    string *arquivoOut;

    int numeroVertices;
    int numeroArestas;

    //private functions
    void leArquivo();
    void exportGrafo();
};

#endif // GRAFO_H_INCLUDED
