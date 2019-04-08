#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Grafo
{
  public:
    Grafo();
    Grafo(string in);
    Grafo(string in, string out);
    ~Grafo();

  private:
    string *arquivoIn;
    string *arquivoOut;

    int numeroVertices;
    int numeroArestas;

    //private functions
    void leArquivo();
    void exportGrafo();
};

#endif // GRAFO_H_INCLUDED
