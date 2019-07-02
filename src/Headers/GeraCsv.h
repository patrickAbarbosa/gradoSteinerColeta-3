#ifndef GERACSV_H_INCLUDED
#define GERACSV_H_INCLUDED

#include <iostream>
#include <fstream>
#include "./LinhaCSV.h"

using namespace std;
// instancia, numero_vertces, numero_aresta, classe, algoritimo, parametro, interacao, tempo_execucao, melhor_solucao
class GeraCsv
{
  public:
    GeraCsv(string arquivoSaida);
    ~GeraCsv();

    void imprime(LinhaCSV linha);
    
  private:
    // nome do arquivo de saida
    string arquivoSaida;
    // numero de linhas do csv
    int numeroLinhas;
    // file stream
    ofstream arquivo;
};

#endif // GERACSV_H