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

using namespace std;

int main(int argc, char *argv[])
{
  cout << "Grupo 03 - Steiner com Coleta de Prêmios" << endl;

  Grafo *a = NULL;

  switch (argc)
  {
  case 1:
    a = new Grafo();
    break;
  case 2:
    a = new Grafo(argv[1]);
    break;
  case 3:
    a = new Grafo(argv[1], argv[2]);
    break;
  case 4:
    a = new Grafo(argv[1], argv[2], argv[3]);
    break;
  default:
    break;
  }

  Guloso guloso(a);
  Grafo * teste = guloso.gulosoRandomizado(1417.943);
  teste->imprimeGrafoPNG();

  /*

  Grafo * agm = guloso.calculaGuloso("5");
  agm->imprimeGrafoPNG();
  delete agm;
  return 0;  
  if (a)
  {
    a->menu();
    delete a;  
  }*/
  return 0;
}
