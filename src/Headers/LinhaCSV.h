#ifndef LINHACSV_H_INCLUDED
#define LINHACSV_H_INCLUDED
#include <iostream>

using namespace std;

// Estrutura da linha do gerador csv
class LinhaCSV {
public:
  string instancia; 
  int numero_vertces;
  int numero_aresta;
  string classe; 
  string algoritmo;
  string parametro; 
  int interacao; 
  string tempo_execucao;
  string melhor_solucao;
};
#endif //LINHACSV_H