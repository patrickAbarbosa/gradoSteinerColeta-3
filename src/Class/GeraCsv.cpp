#include <iostream>
#include <stdlib.h> // exit
#include "../Headers/GeraCsv.h"
#include "../Headers/LinhaCSV.h"

// construtor da classe, recebe o nome do arquivo de saida
GeraCsv::GeraCsv(string arquivoSaida)
{
  this->arquivoSaida = arquivoSaida;
  numeroLinhas = 0;
  arquivo.open(arquivoSaida + ".csv");

  if(!arquivo.is_open())
  {
    cout << "Nao foi possivel abrir o arquivo de saida!" << endl;
    exit(1);
  }
  else
  {
    arquivo << "instancia, numero_vertices, numero_aresta, classe, ";
    arquivo << "algoritimo, parametro, interacao, tempo_execucao(ms), melhor_solucao";
    arquivo << endl;
  }
}

void GeraCsv::imprime(LinhaCSV linha)
{
  arquivo << linha.instancia << ", ";
  arquivo << linha.numero_vertces << ", ";
  arquivo << linha.numero_aresta << ", ";
  arquivo << linha.classe << ", ";
  arquivo << linha.algoritmo << ", ";
  arquivo << linha.parametro << ", ";
  arquivo << linha.interacao << ", ";
  arquivo << linha.tempo_execucao << ", ";
  arquivo << linha.melhor_solucao << endl;

  numeroLinhas++;
}