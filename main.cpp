/*
 * Graph Stenier 
 * 
 * Local: Federal Univercity of Juiz de Fora
 * Authors: Leonardo Nunes and Patrick Barbosa
 * Course: Science Computer
 * 
 * Licence: MIT
 */

#include <iostream>
#include "src/Headers/Grafo.h"
#include "src/Headers/Guloso.h"
#include "src/Headers/GeraCsv.h"

using namespace std;

int main(int argc, char *argv[])
{
  cout << "Grupo 03 - Steiner com Coleta de Prêmios" << endl;

  Grafo *a = NULL;
  GeraCsv *geradorDeArquivo = NULL;
  switch (argc)
  {
  case 1:
    geradorDeArquivo = new GeraCsv("k400.3.con.red");
    a = new Grafo("K400.3.con.red", geradorDeArquivo);
    break;
  case 2:
    geradorDeArquivo = new GeraCsv(argv[1]);
    a = new Grafo(argv[1],geradorDeArquivo);
    break;
  case 3:
    geradorDeArquivo = new GeraCsv(argv[2]);
    a = new Grafo(argv[1], geradorDeArquivo);
    break;
  case 4:
    geradorDeArquivo = new GeraCsv(argv[2]);
    a = new Grafo(argv[1], geradorDeArquivo, argv[3]);
    break;
  default:
    break;
  }

  //Guloso guloso(a);
  Guloso guloso(a);
  
  if (a)
  {
    a->menu();
   
  }
  float vet [10]={0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};

  Grafo * teste = guloso.gulosoRandomizadoReativo(vet,10,2000,100);
  teste->imprimeGrafoPNG();
   delete a;  
  return 0;
}
